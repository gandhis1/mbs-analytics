#ifndef LOAN_H
#define LOAN_H

#include <experimental/optional>
#include <memory>
#include <vector>

#include "constants.h"
#include "prepayment_provision.h"


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
  std::vector<std::shared_ptr<PrepaymentProvision>> originalPrepaymentProvisions;
  double periodicAmortizingDebtService;
  PaymentFrequency paymentFrequency;
  int accrualStartDay;

  std::shared_ptr<PrepaymentProvision> getCurrentPrepaymentProvision(int period) const;

public:
  Loan() = default;
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
       std::experimental::optional<double> periodicAmortizingDebtService = std::experimental::nullopt,
       PaymentFrequency paymentFrequency = PaymentFrequency::MONTHLY,
       int accrualStartDay = 1);
  std::string prettyDescription();
  void prettyPrint();

  friend class CashFlowEngine;
};

#endif