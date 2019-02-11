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
    double originalBalance;
    double currentBalance;
    int originalLoanTerm;
    int originalAmortTerm;
    int originalIOTerm;
    int currentLoanAge;
    double grossCoupon;
    double feeStrip;
    double periodicDebtService;
    PaymentFrequency paymentFrequency;
    std::vector<PrepaymentProvision> original_prepayment_provisions;

  public:
    Loan(double originalBalance,
         double currentBalance,
         int originalLoanTerm,
         int originalAmortTerm,
         int originalIOTerm,
         int currentLoanAge,
         double grossCoupon,
         double feeStrip,
         std::string originalPrepaymentString,
         std::experimental::optional<double> periodicDebtService = std::experimental::nullopt,
         PaymentFrequency paymentFrequency = MONTHLY);
};

#endif