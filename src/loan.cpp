#include <stdexcept>
#include "loan.h"
#include "utilities.h"

Loan::Loan(double originalBalance,
           double currentBalance,
           int originalLoanTerm,
           int originalAmortTerm,
           int originalIOTerm,
           int currentLoanAge,
           double grossCoupon,
           double feeStrip,
           std::string originalPrepaymentString,
           std::experimental::optional<double> periodicDebtService,
           PaymentFrequency paymentFrequency) : originalBalance(originalBalance),
                                                currentBalance(currentBalance),
                                                originalLoanTerm(originalLoanTerm),
                                                originalAmortTerm(originalAmortTerm),
                                                originalIOTerm(originalIOTerm),
                                                currentLoanAge(currentLoanAge),
                                                grossCoupon(grossCoupon),
                                                feeStrip(feeStrip),
                                                paymentFrequency(paymentFrequency)
{
    this->periodicDebtService = periodicDebtService ? Utilities::calculatePayment(originalBalance, originalAmortTerm, grossCoupon) : periodicDebtService.value();

    // TODO: Tokenize and parse the prepayment string, e.g. 'L(30) 5%(24) 4%(24) 3%(12) 2%(12) 1%(12) O(6)'
    if (originalPrepaymentString == "L(30) 5%(24) 4%(24) 3%(12) 2%(12) 1%(12) O(6)")
    {
        original_prepayment_provisions.push_back(Lockout(30));
        original_prepayment_provisions.push_back(FixedPenalty(24, 0.05));
        original_prepayment_provisions.push_back(FixedPenalty(24, 0.04));
        original_prepayment_provisions.push_back(FixedPenalty(12, 0.03));
        original_prepayment_provisions.push_back(FixedPenalty(12, 0.02));
        original_prepayment_provisions.push_back(FixedPenalty(12, 0.01));
        original_prepayment_provisions.push_back(Open(6));
    }
    else
    {
        throw std::invalid_argument("Custom prepayment strings are not yet supported");
    }
}
