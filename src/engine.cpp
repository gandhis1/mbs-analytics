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
            double beginningBalance;
            double endingBalance;
            double grossInterest;
            double netInterest;
            double coupon;
            double scheduledPrincipal;
            double unscheduledPrincipal;
            double loss;
            double prepayPenalty;

            for (int period = 0; period < scenario.scenarioLength; ++period)
            {
                double smm = Utilities::changeCompoundingBasis(scenario.vprVector[period], 1, 12);
                //double mdr = Utilities::changeCompoundingBasis(scenario.cdrVector[period], 1, 12);
                if (period == 0)
                {
                    paymentDate = loan.factorDate;;
                    endingBalance = beginningBalance = loan.currentBalance;
                    grossInterest = 0.0;
                    netInterest = 0.0;
                    coupon = 0.0;
                    scheduledPrincipal = 0.0;
                    unscheduledPrincipal = 0.0;
                    loss = 0.0;
                    prepayPenalty = 0.0;
                }
                else
                {
                    // Calculate all cash flows based on the current fractions
                    beginningBalance = endingBalance;
                    // ++paymentDate.tm_mon;
                    // paymentDate = *localtime((const time_t *)mktime(&paymentDate));
                    grossInterest = loan.grossCoupon * (loan.paymentFrequency / 12.0) * beginningBalance;
                    netInterest = loan.netCoupon() * (loan.paymentFrequency / 12.0) * beginningBalance;
                    coupon = loan.grossCoupon;
                    scheduledPrincipal = std::max(loan.periodicAmortizingDebtService - grossInterest, 0.0);
                    unscheduledPrincipal = smm * (beginningBalance - scheduledPrincipal);
                    loss = 0.0;
                    prepayPenalty = 0.0;
                    endingBalance = beginningBalance - scheduledPrincipal - unscheduledPrincipal;
                }

                // Pay off the loan at the balloon date
                if (period >= loan.originalLoanTerm)
                {
                    // TODO: Keep track of balloon principal amounts separately
                    scheduledPrincipal += endingBalance;
                    scheduledPrincipal += unscheduledPrincipal;
                    unscheduledPrincipal = 0;
                    endingBalance = 0;
                }

                CashFlow periodicCashflow;
                periodicCashflow.paymentDate = paymentDate; // TODO: Use real dates
                periodicCashflow.endingBalance = endingBalance;
                periodicCashflow.grossInterest = grossInterest;
                periodicCashflow.netInterest = netInterest;
                periodicCashflow.coupon = coupon;
                periodicCashflow.scheduledPrincipal = scheduledPrincipal;
                periodicCashflow.unscheduledPrincipal = unscheduledPrincipal;
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