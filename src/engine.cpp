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
            struct tm paymentDate;
            struct tm accrualStartDate;
            struct tm accrualEndDate;
            double beginningBalance;
            double endingBalance;
            double grossInterest;
            double netInterest;
            double coupon;
            double scheduledPrincipal;
            double unscheduledPrincipal;
            double balloonPrincipal;
            double loss;
            double prepayPenalty;

            for (int period = 0; period < scenario.scenarioLength; period += loan.paymentFrequency)
            {
                double smm = Utilities::changeCompoundingBasis(scenario.vprVector[period], 1, 12);
                //double mdr = Utilities::changeCompoundingBasis(scenario.cdrVector[period], 1, 12);
                if (period == 0)
                {
                    paymentDate = loan.factorDate;
                    accrualStartDate = Utilities::addDateInterval(paymentDate, 0, -loan.paymentFrequency, 0);
                    accrualStartDate.tm_mday = loan.accrualStartDay;
                    accrualEndDate = Utilities::addDateInterval(paymentDate, 0, 0, -paymentDate.tm_mday);
                    endingBalance = beginningBalance = loan.currentBalance;
                    grossInterest = 0.0;
                    netInterest = 0.0;
                    coupon = 0.0;
                    scheduledPrincipal = 0.0;
                    unscheduledPrincipal = 0.0;
                    balloonPrincipal = 0.0;
                    loss = 0.0;
                    prepayPenalty = 0.0;
                }
                else
                {
                    // Handle the dates first
                    paymentDate = Utilities::addDateInterval(paymentDate, 0, loan.paymentFrequency, 0);
                    accrualStartDate = Utilities::addDateInterval(accrualEndDate, 0, 0, 1);
                    accrualEndDate = paymentDate;
                    accrualEndDate.tm_mday = 1;
                    accrualEndDate = Utilities::addDateInterval(accrualEndDate, 0, 0, -1);
                    int accrualDayCount = 30; // Assume THIRTY_360 by default
                    if (loan.accrualBasis == ACTUAL_360)
                    {
                        accrualDayCount = Utilities::daysBetween(accrualEndDate, accrualStartDate);
                    }
                    double accrualFraction = accrualDayCount / 360.0;

                    // Calculate all cash flows based on the current fractions
                    beginningBalance = endingBalance;
                    grossInterest = loan.grossCoupon * accrualFraction * beginningBalance;
                    netInterest = loan.netCoupon() * accrualFraction * beginningBalance;
                    coupon = loan.grossCoupon;
                    scheduledPrincipal = std::max(loan.periodicAmortizingDebtService - grossInterest, 0.0);
                    unscheduledPrincipal = smm * (beginningBalance - scheduledPrincipal);
                    balloonPrincipal = 0.0;
                    loss = 0.0;
                    prepayPenalty = 0.0;
                    endingBalance = beginningBalance - scheduledPrincipal - unscheduledPrincipal;
                }

                // Pay off the loan at the balloon date
                if (period >= loan.originalLoanTerm)
                {
                    // TODO: Keep track of balloon principal amounts separately
                    balloonPrincipal = endingBalance;
                    scheduledPrincipal += unscheduledPrincipal;
                    unscheduledPrincipal = 0;
                    endingBalance = 0;
                }

                CashFlow periodicCashflow;
                periodicCashflow.paymentDate = paymentDate;
                periodicCashflow.accrualStartDate = accrualStartDate;
                periodicCashflow.accrualEndDate = accrualEndDate;
                periodicCashflow.endingBalance = endingBalance;
                periodicCashflow.grossInterest = grossInterest;
                periodicCashflow.netInterest = netInterest;
                periodicCashflow.coupon = coupon;
                periodicCashflow.scheduledPrincipal = scheduledPrincipal;
                periodicCashflow.unscheduledPrincipal = unscheduledPrincipal;
                periodicCashflow.balloonPrincipal = balloonPrincipal;
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
