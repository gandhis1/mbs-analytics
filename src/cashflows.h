#ifndef CASHFLOWS_H
#define CASHFLOWS_H

#include <ctime>

class CashFlows
{
  private:
    std::vector<std::time_t> paymentDate;
    std::vector<double> endingBalance;
    std::vector<double> grossInterest;
    std::vector<double> netInterest;
    std::vector<double> coupon;
    std::vector<double> principal;
    std::vector<double> loss;
    std::vector<double> prepayPenalty;
    std::map<std::string, std::map<int, std::map<std::string, double>>> rawCashflows;

  public:
    double yieldToMaturity(std::time_t settleDate, double price);
    double weightedAverageLife(std::time_t settleDate);
    friend class CashFlowEngine;
};

#endif