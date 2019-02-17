#include <ctime>
#include <iostream>
#include <iomanip>

#include "cashflows.h"
#include "utilities.h"

void CashFlows::prettyPrint()
{
    const int WIDTH = 17;
    std::cout << std::left << std::setw(10) << std::setfill(' ') << "Period"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Payment Date"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Accrual Start"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Accrual End"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Accrual Days"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Ending Balance"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Sched Prin"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Unsched Prin"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Balloon Prin"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Total Prin"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Realized Loss"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Gross Coupon"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Net Coupon"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Sched Payment"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Gross Interest"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Net Interest"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Prepay Penalty"
              << std::endl;
    for (unsigned short i = 0; i < periodicCashflows.size(); ++i)
    {
        auto &cashflow = periodicCashflows[i];
        // char paymentDateStr[8];
        // strftime(paymentDateStr, sizeof(paymentDateStr), "%Y-%m-%d", (const struct tm*)&cashflow.paymentDate);
        std::cout
            << std::left << std::setw(10) << std::setprecision(2) << std::fixed << std::setfill(' ') << i
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << Utilities::toYYYYMMDD(cashflow.paymentDate)
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << Utilities::toYYYYMMDD(cashflow.accrualStartDate)
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << Utilities::toYYYYMMDD(cashflow.accrualEndDate)
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.accrualDays
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.endingBalance
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.scheduledPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.unscheduledPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.balloonPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.totalPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.loss
            << std::left << std::setw(WIDTH) << std::setprecision(4) << std::fixed << std::setfill(' ') << cashflow.grossCoupon
            << std::left << std::setw(WIDTH) << std::setprecision(4) << std::fixed << std::setfill(' ') << cashflow.netCoupon
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.scheduledPayment
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.grossInterest
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.netInterest
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.prepayPenalty
            << std::endl;
    }
}