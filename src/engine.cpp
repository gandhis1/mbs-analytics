#include <algorithm>
#include <iostream>
#include <map>

#include "engine.h"
#include "utilities.h"

CashFlows CashFlowEngine::runCashflows(
    Deal &deal,
    Scenario &scenario)
{
    std::map<std::string, CashFlows> loanFlows;
    std::map<std::string, CashFlows> groupFlows;
    for  (auto& groupIdtoGroup: deal.collateral)
    {
        auto& group = groupIdtoGroup.second;

        for (Loan& loan: group.loans)
        {
            time_t factorDate = loan.factorDate;
            time_t paymentDate;
            double endingBalance;
            double grossInterest;
            double netInterest;
            double coupon;
            double principal;
            double loss;
            double prepayPenalty;
            for (int period = 0; period < scenario.scenarioLength; ++period)
            {
                if (period == 0)
                {
                    paymentDate = factorDate;
                    endingBalance = loan.currentBalance;
                    grossInterest = 0.0;
                    netInterest = 0.0;
                    coupon = 0.0;
                    principal = 0.0;
                    loss = 0.0;
                    prepayPenalty = 0.0;
                }
                else {
                    paymentDate += 60 * 60 * 24 * 30;
                    grossInterest = loan.grossCoupon * endingBalance;
                    netInterest = loan.netCoupon() * endingBalance;
                    coupon = loan.grossCoupon;
                    principal = std::max(loan.periodicAmortizingDebtService - grossInterest, 0.0);
                    loss = 0.0;
                    prepayPenalty = 0.0;
                    endingBalance -= principal;
                }
                loanFlows[loan.id].paymentDate.push_back(endingBalance);  // TODO: Use real dates
                loanFlows[loan.id].endingBalance.push_back(endingBalance);
                loanFlows[loan.id].grossInterest.push_back(grossInterest);
                loanFlows[loan.id].netInterest.push_back(netInterest);
                loanFlows[loan.id].coupon.push_back(coupon);
                loanFlows[loan.id].principal.push_back(principal);
                loanFlows[loan.id].loss.push_back(loss);
                loanFlows[loan.id].prepayPenalty.push_back(prepayPenalty);

                if (endingBalance < Utilities::EPSILON)
                {
                    break;
                }
                // TOOD: check maturity date and if guaranteed or take a loss
            }
        }
    }
    return std::move(groupFlows["all"]);
}