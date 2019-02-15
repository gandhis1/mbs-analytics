#ifndef CASHFLOWS_H
#define CASHFLOWS_H

#include <ctime>

class CashFlow
{
public:
  time_t paymentDate;
  double endingBalance;
  double grossInterest;
  double netInterest;
  double coupon;
  double scheduledPrincipal;
  double unscheduledPrincipal;
  double loss;
  double prepayPenalty;
};

class CashFlows
{
private:
  std::vector<CashFlow> periodicCashflows;

public:
  template <typename Container>
  static CashFlows aggregateCashFlows(Container container)
  {
    CashFlows retCashFlows;
    for (auto element : container)
    {
      // TODO: Actually aggregate the flows
      retCashFlows = element.second;
    }
    return retCashFlows;
  }
  double yieldToMaturity(std::time_t settleDate, double price);
  double weightedAverageLife(std::time_t settleDate);
  friend class CashFlowEngine;
};

#endif
