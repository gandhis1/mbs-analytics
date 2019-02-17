#include <memory>
#include <stdexcept>
#include "loan.h"
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

    // TODO: Actually tokenize and parse the prepayment string
    if (originalPrepaymentString == "L(24) 5%(24) 4%(24) 3%(12) 2%(12) 1%(12) O(12)")
    {
        originalPrepaymentProvisions.push_back(std::make_shared<Lockout>(24));
        originalPrepaymentProvisions.push_back(std::make_shared<FixedPenalty>(24, 0.05));
        originalPrepaymentProvisions.push_back(std::make_shared<FixedPenalty>(24, 0.04));
        originalPrepaymentProvisions.push_back(std::make_shared<FixedPenalty>(12, 0.03));
        originalPrepaymentProvisions.push_back(std::make_shared<FixedPenalty>(12, 0.02));
        originalPrepaymentProvisions.push_back(std::make_shared<FixedPenalty>(12, 0.01));
        originalPrepaymentProvisions.push_back(std::make_shared<Open>(12));
    }
    else
    {
        throw std::invalid_argument("Custom prepayment strings are not yet supported");
    }
}
