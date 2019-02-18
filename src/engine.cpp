#include <algorithm>
#include <iostream>
#include <map>

#include "engine.h"
#include "cashflows.h"
#include "utilities.h"

CashFlows CashFlowEngine::runCashflows(
    Deal &deal,
    Scenario &scenario)
{
    // Cash flows will be generated in separate stages:
    // First - run the loan-level using the scenario assumptions
    // Second - aggregate to the group-level
    // Third - if any bond structure is available, run through the waterfall (TODO)
    std::map<std::string, CashFlows> groupFlows;
    for (auto &groupIdtoGroup : deal.collateral)
    {
        auto &groupId = groupIdtoGroup.first;
        auto &group = groupIdtoGroup.second;
        std::map<std::string, CashFlows> loanFlows;
        for (Loan &loan : group.loans)
        {
            struct tm paymentDate = loan.factorDate;
            struct tm accrualStartDate = Utilities::addDateInterval(paymentDate, 0, -loan.paymentFrequency, 0);
            accrualStartDate.tm_mday = loan.accrualStartDay;
            struct tm accrualEndDate = Utilities::addDateInterval(paymentDate, 0, 0, -paymentDate.tm_mday);
            unsigned short accrualDays = 0;
            double beginningBalance = loan.currentBalance;
            double endingBalance = loan.currentBalance;
            double grossCoupon = NAN;
            double netCoupon = NAN;
            double grossInterest = NAN;
            double netInterest = NAN;
            double scheduledPrincipal = NAN;
            double unscheduledPrincipal = NAN;
            double balloonPrincipal = NAN;
            double defaultAmount = NAN;
            std::map<int, double> realizedLossByPeriod;      // To handle lags
            std::map<int, double> recoveryPrincipalByPeriod; // To handle lags
            double prepayPenalty = NAN;
            double performingFraction = 1.0;
            double prepaidFraction = 0.0;
            double defaultedFraction = 0.0;
            loanFlows[loan.id].periodicCashflows.reserve(loan.originalLoanTerm - loan.currentLoanAge);  // Reserve memory to avoid copy

            for (unsigned short period = 0; period < scenario.MAX_PERIODS; period += loan.paymentFrequency)
            {
                if (period >= 1)
                {
                    // Handle the dates first
                    paymentDate = Utilities::addDateInterval(paymentDate, 0, loan.paymentFrequency, 0);
                    accrualStartDate = Utilities::addDateInterval(accrualEndDate, 0, 0, 1);
                    accrualEndDate = paymentDate;
                    accrualEndDate.tm_mday = 1;
                    accrualEndDate = Utilities::addDateInterval(accrualEndDate, 0, 0, -1);
                    accrualDays = 30; // Assume THIRTY_360 by default
                    if (loan.accrualBasis == ACTUAL_360)
                    {
                        accrualDays = Utilities::daysBetween(accrualStartDate, accrualEndDate, true);
                    }
                    double accrualFraction = accrualDays / 360.0;

                    // Handle the speeds calculations
                    PrepaymentProvision &currentPrepaymentProvision = *PrepaymentProvision::getCurrentPrepaymentProvision(loan.originalPrepaymentProvisions, loan.currentLoanAge + period);
                    double smm = currentPrepaymentProvision.canVoluntarilyPrepay() ? Utilities::changeCompoundingBasis(scenario.vprVector[period], 1, 12) : 0.0;
                    double mdr = Utilities::changeCompoundingBasis(scenario.cdrVector[period], 1, 12);
                    double sev = scenario.sevVector[period];
                    int lag = scenario.lagVector[period];

                    // Calculate all cash flows based on the current fractions
                    beginningBalance = endingBalance;
                    if (beginningBalance > Utilities::EPSILON)
                    {
                        grossCoupon = loan.grossCoupon;
                        netCoupon = loan.netCoupon;
                        grossInterest = loan.grossCoupon * accrualFraction * beginningBalance;
                        netInterest = loan.netCoupon * accrualFraction * beginningBalance;
                        bool isInInterestOnlyPeriod = (loan.currentLoanAge + period) <= loan.originalIOTerm;                           
                        scheduledPrincipal = isInInterestOnlyPeriod ? 0.0 : std::max(loan.periodicAmortizingDebtService * performingFraction - grossInterest, 0.0);
                        unscheduledPrincipal = smm * (beginningBalance - scheduledPrincipal);
                        balloonPrincipal = 0.0;
                        defaultAmount = mdr * (beginningBalance - scheduledPrincipal);
                        realizedLossByPeriod[period + lag] = defaultAmount * sev;
                        recoveryPrincipalByPeriod[period + lag] = defaultAmount * (1 - sev);
                        prepayPenalty = (unscheduledPrincipal > 0.0) ? currentPrepaymentProvision.calculatePrepaymentPenalty(unscheduledPrincipal) : 0.0;
                        endingBalance = beginningBalance - scheduledPrincipal - unscheduledPrincipal;

                        // Adjust the ending balance fractions
                        double newPrepays = performingFraction * smm;
                        double newDefaults = performingFraction * mdr;
                        prepaidFraction += newPrepays;
                        defaultedFraction += newDefaults;
                        performingFraction -= (newPrepays + newDefaults);

                        // Pay off the loan at the balloon date
                        if (loan.currentLoanAge + period >= loan.originalLoanTerm)
                        {
                            if (beginningBalance > 0.0)
                            {
                                balloonPrincipal = endingBalance;
                                scheduledPrincipal += unscheduledPrincipal;
                                unscheduledPrincipal = 0;
                                endingBalance = 0;

                                if (!scenario.extendLagsPastMaturity)
                                {
                                    for (auto const &periodAndRecovery : recoveryPrincipalByPeriod)
                                    {
                                        if (periodAndRecovery.first > period)
                                        {
                                            recoveryPrincipalByPeriod[period] += periodAndRecovery.second;
                                        }
                                    }
                                    for (auto const &periodAndLoss : realizedLossByPeriod)
                                    {
                                        if (periodAndLoss.first > period)
                                        {
                                            realizedLossByPeriod[period] += periodAndLoss.second;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                CashFlow periodicCashflow;
                periodicCashflow.period = period;
                periodicCashflow.paymentDate = paymentDate;
                periodicCashflow.accrualStartDate = accrualStartDate;
                periodicCashflow.accrualEndDate = accrualEndDate;
                periodicCashflow.accrualDays = accrualDays;
                periodicCashflow.endingBalance = endingBalance;
                if (beginningBalance > Utilities::EPSILON)
                {
                    periodicCashflow.grossCoupon = grossCoupon;
                    periodicCashflow.netCoupon = netCoupon;
                    periodicCashflow.grossInterest = grossInterest;
                    periodicCashflow.netInterest = netInterest;
                    periodicCashflow.scheduledPrincipal = scheduledPrincipal;
                    periodicCashflow.unscheduledPrincipal = unscheduledPrincipal;
                    periodicCashflow.balloonPrincipal = balloonPrincipal;
                    periodicCashflow.defaultAmount = defaultAmount;
                    periodicCashflow.prepayPenalty = prepayPenalty;
                }
                periodicCashflow.realizedLoss = realizedLossByPeriod.count(period) ? realizedLossByPeriod[period] : ((period > 0) ? 0.0 : NAN);
                periodicCashflow.recoveryPrincipal = recoveryPrincipalByPeriod.count(period) ? recoveryPrincipalByPeriod[period] : ((period > 0) ? 0.0 : NAN);
                loanFlows[loan.id].periodicCashflows.emplace_back(periodicCashflow);
                // Only break off the amort if the ending balance is zero or there are still recoveries due in future
                int maxRecoveryPeriod = recoveryPrincipalByPeriod.size() > 0 ? (*--recoveryPrincipalByPeriod.end()).first : 0;
                if (endingBalance < Utilities::EPSILON && (!scenario.extendLagsPastMaturity or period >= maxRecoveryPeriod))
                {
                    break;
                }
            }
        }
        groupFlows[groupId] = CashFlows::aggregateCashFlows(loanFlows);
    }
    return std::move(groupFlows["all"]); // Temporary until a more well-structured object is available for each level of cash flows
}
