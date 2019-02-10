#include "loan.h"
#include "utilities.h"

Loan::Loan(double originalBalance,
           double cutoffBalance,
           int originalLoanTerm,
           int originalAmortTerm,
           int originalIOTerm,
           int seasoning,
           double grossCoupon,
           double feeStrip,
           std::experimental::optional<double> periodicDebtService,
           PaymentFrequency paymentFrequency) : originalBalance(originalBalance),
                                                cutoffBalance(cutoffBalance),
                                                originalLoanTerm(originalLoanTerm),
                                                originalAmortTerm(originalAmortTerm),
                                                originalIOTerm(originalIOTerm),
                                                seasoning(seasoning),
                                                grossCoupon(grossCoupon),
                                                feeStrip(feeStrip),
                                                paymentFrequency(paymentFrequency)
{
    if (periodicDebtService)
    {
        this->periodicDebtService = periodicDebtService.value();
    }
    else
    {
        this->periodicDebtService = Utilities::calculatePayment(cutoffBalance, originalAmortTerm - seasoning, grossCoupon);
    }
}
