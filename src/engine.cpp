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
    std::map<std::string, CashFlows> groupFlows;
    for (auto &groupIdtoGroup : deal.collateral)
    {
        auto &groupId = groupIdtoGroup.first;
        auto &group = groupIdtoGroup.second;
        std::map<std::string, CashFlows> loanFlows;
        for (Loan &loan : group.loans)
        {
            struct tm paymentDate = loan.factorDate;;
            struct tm accrualStartDate = Utilities::addDateInterval(paymentDate, 0, -loan.paymentFrequency, 0);
            accrualStartDate.tm_mday = loan.accrualStartDay;
            struct tm accrualEndDate = Utilities::addDateInterval(paymentDate, 0, 0, -paymentDate.tm_mday);
            unsigned short accrualDays = 0;
            double beginningBalance = loan.currentBalance;
            double endingBalance = loan.currentBalance;
            double grossCoupon = 0.0;
            double netCoupon = 0.0;
            double grossInterest = 0.0;
            double netInterest = 0.0;
            double scheduledPrincipal = 0.0;
            double unscheduledPrincipal = 0.0;
            double balloonPrincipal = 0.0;
            double scheduledPayment = 0.0;
            double loss = 0.0;
            double prepayPenalty = 0.0;
            double performingFraction = 1.0;
            double prepaidFraction = 0.0;
            double defaultedFraction = 0.0;

            for (int period = 0; period < scenario.scenarioLength; period += loan.paymentFrequency)
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
                    double smm = Utilities::changeCompoundingBasis(scenario.vprVector[period], 1, 12);
                    double mdr = Utilities::changeCompoundingBasis(scenario.cdrVector[period], 1, 12);

                    // Calculate all cash flows based on the current fractions
                    beginningBalance = endingBalance;
                    grossCoupon = loan.grossCoupon;
                    netCoupon = loan.netCoupon;
                    grossInterest = loan.grossCoupon * accrualFraction * beginningBalance;
                    netInterest = loan.netCoupon * accrualFraction * beginningBalance;
                    scheduledPayment = loan.periodicAmortizingDebtService * performingFraction;
                    scheduledPrincipal = std::max(scheduledPayment - grossInterest, 0.0);
                    unscheduledPrincipal = smm * (beginningBalance - scheduledPrincipal);
                    balloonPrincipal = 0.0;
                    loss = 0.0;
                    prepayPenalty = 0.0;
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
                        // TODO: Keep track of balloon principal amounts separately
                        balloonPrincipal = endingBalance;
                        scheduledPrincipal += unscheduledPrincipal;
                        unscheduledPrincipal = 0;
                        endingBalance = 0;
                    }
                }


                CashFlow periodicCashflow;
                periodicCashflow.paymentDate = paymentDate;
                periodicCashflow.accrualStartDate = accrualStartDate;
                periodicCashflow.accrualEndDate = accrualEndDate;
                periodicCashflow.accrualDays = accrualDays;
                periodicCashflow.endingBalance = endingBalance;
                periodicCashflow.grossCoupon = grossCoupon;
                periodicCashflow.netCoupon = netCoupon;
                periodicCashflow.grossInterest = grossInterest;
                periodicCashflow.netInterest = netInterest;
                periodicCashflow.scheduledPrincipal = scheduledPrincipal;
                periodicCashflow.unscheduledPrincipal = unscheduledPrincipal;
                periodicCashflow.balloonPrincipal = balloonPrincipal;
                periodicCashflow.totalPrincipal = scheduledPrincipal + unscheduledPrincipal + balloonPrincipal;
                periodicCashflow.scheduledPayment = scheduledPayment;
                periodicCashflow.loss = loss;
                periodicCashflow.prepayPenalty = prepayPenalty;
                loanFlows[loan.id].periodicCashflows.push_back(periodicCashflow);
                if (endingBalance < Utilities::EPSILON)
                {
                    break;
                }
            }
        }
        groupFlows[groupId] = CashFlows::aggregateCashFlows(loanFlows);
    }
    return std::move(groupFlows["all"]);
}
