#include <iomanip>
#include <iostream>
#include <memory>
#include "constants.h"
#include "loan.h"
#include "prepayment_provision.h"
#include "utilities.h"

Loan::Loan(std::string id,
           double originalBalance,
           double currentBalance,
           struct tm firstPaymentDate,
           struct tm factorDate,
           int originalLoanTerm,
           int originalAmortTerm,
           int originalIOTerm,
           double grossCoupon,
           double feeStrip,
           AccrualBasis accrualBasis,
           std::string originalPrepaymentString,
           std::experimental::optional<double> periodicAmortizingDebtService,
           PaymentFrequency paymentFrequency,
           int accrualStartDay) : id(id),
                                  originalBalance(originalBalance),
                                  currentBalance(currentBalance),
                                  firstPaymentDate(firstPaymentDate),
                                  factorDate(factorDate),
                                  originalLoanTerm(originalLoanTerm),
                                  originalAmortTerm(originalAmortTerm),
                                  originalIOTerm(originalIOTerm),
                                  grossCoupon(grossCoupon),
                                  feeStrip(feeStrip),
                                  accrualBasis(accrualBasis),
                                  paymentFrequency(paymentFrequency),
                                  accrualStartDay(accrualStartDay)
{
    currentLoanAge = Utilities::DateTime::monthsBetween(firstPaymentDate, factorDate);
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

std::shared_ptr<PrepaymentProvision> Loan::getCurrentPrepaymentProvision(int period) const
{
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

std::string Loan::prettyDescription()
{
    std::string prepaymentString = summarizePrepaymentProvisions(originalPrepaymentProvisions);
    const int LABEL_WIDTH = 15;
    const int VALUE_WIDTH = std::max(12, static_cast<int>(prepaymentString.length() + 1));
    std::string border = std::string(LABEL_WIDTH + VALUE_WIDTH, '*');
    std::ostringstream textstream;
    textstream
        << border << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "LOAN ID: " << std::setw(VALUE_WIDTH) << id << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "ORIG BAL: " << std::setw(VALUE_WIDTH) << originalBalance << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "CURR BAL: " << std::setw(VALUE_WIDTH) << currentBalance << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "FACTOR DATE: " << std::setw(VALUE_WIDTH) << Utilities::DateTime::toYYYYMMDD(factorDate) << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "ORIG TERM: " << std::setw(VALUE_WIDTH) << originalLoanTerm << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "ORIG AMORT: " << std::setw(VALUE_WIDTH) << originalAmortTerm << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "ORIG IO: " << std::setw(VALUE_WIDTH) << originalIOTerm << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "CURR AGE: " << std::setw(VALUE_WIDTH) << currentLoanAge << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "GROSS CPN: " << std::setw(VALUE_WIDTH) << grossCoupon << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "FEE STRIP: " << std::setw(VALUE_WIDTH) << feeStrip << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "NET CPN: " << std::setw(VALUE_WIDTH) << netCoupon << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "DAY COUNT: " << std::setw(VALUE_WIDTH) << enumToString(accrualBasis) << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "PAY FREQ: " << std::setw(VALUE_WIDTH) << paymentFrequency << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "ACCR START: " << std::setw(VALUE_WIDTH) << accrualStartDay << std::endl
        << std::left << std::setw(LABEL_WIDTH) << "PENALTY STR: " << std::setw(VALUE_WIDTH) << prepaymentString << std::endl
        << border << std::endl;
    return textstream.str();
}

void Loan::prettyPrint()
{
    std::cout << prettyDescription();
}