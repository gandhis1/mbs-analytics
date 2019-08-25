#ifndef CASHFLOWS_H
#define CASHFLOWS_H

#include <ctime>
#include <vector>

class CashFlow
{
public:
  CashFlow();
  unsigned short period;
  struct tm paymentDate;
  struct tm accrualStartDate;
  struct tm accrualEndDate;
  unsigned short accrualDays;
  double endingBalance;
  double grossCoupon;
  double netCoupon;
  double grossInterest;
  double netInterest;
  double scheduledPrincipal;
  double unscheduledPrincipal;
  double balloonPrincipal;
  double recoveryPrincipal;
  double defaultAmount;
  double realizedLoss;
  double prepayPenalty;

  // Derived fields based on values above
  double scheduledPayment();
  double totalPrincipal();
  double totalCashflow();
  double penaltyRate();
};

class CashFlows
{
private:
  std::vector<CashFlow> periodicCashflows;
public:
  std::string prettyDescription();
  void prettyPrint();
  double yieldToMaturity(struct tm settleDate, double price);
  double weightedAverageLife(struct tm settleDate);
  friend class CashFlowEngine;
  template <typename PairContainer> // Assume std::map for now, use type_traits later
  static CashFlows aggregateCashFlows(PairContainer container)
  {
    CashFlows retCashFlows;
    for (auto &element : container)
    {
      // TODO: Actually aggregate the flows
      retCashFlows = element.second;
    }
    return retCashFlows;
  }
};

#endif
