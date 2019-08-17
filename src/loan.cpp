#include <memory>
#include <stdexcept>
#include "loan.h"
#include "prepayment_provision.h"
#include "utilities.h"

Loan::Loan(std::string id,
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
           std::experimental::optional<double> periodicAmortizingDebtService,
           PaymentFrequency paymentFrequency,
           int accrualStartDay) : id(id),
                                  originalBalance(originalBalance),
                                  currentBalance(currentBalance),
                                  factorDate(factorDate),
                                  originalLoanTerm(originalLoanTerm),
                                  originalAmortTerm(originalAmortTerm),
                                  originalIOTerm(originalIOTerm),
                                  currentLoanAge(currentLoanAge),
                                  grossCoupon(grossCoupon),
                                  feeStrip(feeStrip),
                                  accrualBasis(accrualBasis),
                                  paymentFrequency(paymentFrequency),
                                  accrualStartDay(accrualStartDay)
{
    netCoupon = grossCoupon - feeStrip;
    if (periodicAmortizingDebtService)
    {
        this->periodicAmortizingDebtService = periodicAmortizingDebtService.value();
    }
    else
    {
        double periodicGrossCoupon = grossCoupon * paymentFrequency / 12.0;
        this->periodicAmortizingDebtService = Utilities::calculatePayment(originalBalance, originalAmortTerm, periodicGrossCoupon);
    }
    originalPrepaymentProvisions = parsePrepaymentString(originalPrepaymentString);
}

std::shared_ptr<PrepaymentProvision> Loan::getCurrentPrepaymentProvision(int period) {
    // TODO: This function is inefficient as it is constantly re-indexing the vector - but works for now
    int loanAge = currentLoanAge + period;
    int cumulativePayments = 0;
    for (unsigned short i = 0; i < originalPrepaymentProvisions.size(); ++i)
    {
        if (loanAge > cumulativePayments && loanAge <= cumulativePayments + originalPrepaymentProvisions[i]->length)
        {
            return originalPrepaymentProvisions[i];
        }
        else
        {
            cumulativePayments += originalPrepaymentProvisions[i]->length;
        }
    }
    return originalPrepaymentProvisions.back();
}
