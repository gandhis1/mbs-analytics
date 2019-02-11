#ifndef LOAN_H
#define LOAN_H

#include <experimental/optional>
#include <vector>
#include "prepayment_provision.h"

enum PaymentFrequency
{
    MONTHLY = 1,
    QUARTERLY = 3,
    SEMIANNUALLY = 6,
    ANNUALLY = 12
};

class Loan
{
  private:
    std::string id;
    double originalBalance;
    double currentBalance;
    time_t factorDate;
    int originalLoanTerm;
    int originalAmortTerm;
    int originalIOTerm;
    int currentLoanAge;
    double grossCoupon;
    double netCoupon();
    double feeStrip;
    double periodicAmortizingDebtService;
    PaymentFrequency paymentFrequency;
    std::vector<PrepaymentProvision> original_prepayment_provisions;

  public:
    Loan(std::string id,
         double originalBalance,
         double currentBalance,
         time_t factorDate,
         int originalLoanTerm,
         int originalAmortTerm,
         int originalIOTerm,
         int currentLoanAge,
         double grossCoupon,
         double feeStrip,
         std::string originalPrepaymentString,
         std::experimental::optional<double> periodicDebtService = std::experimental::nullopt,
         PaymentFrequency paymentFrequency = MONTHLY);

    friend class CashFlowEngine;
};

#endif