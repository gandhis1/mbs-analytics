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

enum AccrualBasis
{
  THIRTY_360,
  ACTUAL_360
};

class Loan
{
private:
  std::string id;
  double originalBalance;
  double currentBalance;
  struct tm factorDate;
  int originalLoanTerm;
  int originalAmortTerm;
  int originalIOTerm;
  int currentLoanAge;
  double grossCoupon;
  double netCoupon;
  double feeStrip;
  AccrualBasis accrualBasis;
  std::vector<PrepaymentProvision> originalPrepaymentProvisions;
  double periodicAmortizingDebtService;
  PaymentFrequency paymentFrequency;
  int accrualStartDay;

public:
  Loan(std::string id,
       double originalBalance,
       double currentBalance,
       struct tm factorDate,
       int originalLoanTerm,
       int originalAmortTerm,
       int originalIOTerm,
       int currentLoanAge,
       double grossCoupon,
       double feeStrip,
       AccrualBasis accrualBasis,
       std::string originalPrepaymentString,
       std::experimental::optional<double> periodicDebtService = std::experimental::nullopt,
       PaymentFrequency paymentFrequency = MONTHLY,
       int accrualStartDay = 1);

  friend class CashFlowEngine;
};

#endif