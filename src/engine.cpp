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
            time_t paymentDate;
            double beginningBalance;
            double endingBalance;
            double grossInterest;
            double netInterest;
            double coupon;
            double scheduledPrincipal;
            double unscheduledPrincipal;
            double loss;
            double prepayPenalty;
            double survivalFraction = 1.0;

            for (int period = 0; period < scenario.scenarioLength; ++period)
            {
                double smm = Utilities::changeCompoundingBasis(scenario.vprVector[period], 1, 12);
                double mdr = Utilities::changeCompoundingBasis(scenario.cdrVector[period], 1, 12);
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
                    paymentDate += 60 * 60 * 24 * 30;
                    grossInterest = loan.grossCoupon * beginningBalance * survivalFraction;
                    netInterest = loan.netCoupon() * beginningBalance * survivalFraction;
                    coupon = loan.grossCoupon;
                    scheduledPrincipal = std::max(loan.periodicAmortizingDebtService * survivalFraction - grossInterest, 0.0);
                    unscheduledPrincipal = smm * (beginningBalance - scheduledPrincipal);
                    loss = 0.0;
                    prepayPenalty = 0.0;
                    endingBalance = beginningBalance - scheduledPrincipal - unscheduledPrincipal;
                    survivalFraction = survivalFraction * (1 - smm) * (1 - mdr);
                }

                // TODO: check maturity date and if guaranteed or take a loss

                CashFlow periodicCashflow;
                periodicCashflow.paymentDate = endingBalance; // TODO: Use real dates
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