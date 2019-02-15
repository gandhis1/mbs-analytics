#include <ctime>
#include <iostream>
#include <iomanip>

#include "cashflows.h"

void CashFlows::prettyPrint()
{
    const int WIDTH = 12;
    std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << "Period"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Balance"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Sched"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Unsched"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Principal"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Loss"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Coupon"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Payment"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Gross"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Net"
              << std::left << std::setw(WIDTH) << std::setfill(' ') << "Penalty"
              << std::endl;
    for (unsigned int i = 0; i < periodicCashflows.size(); ++i)
    {
        auto &cashflow = periodicCashflows[i];
        // char paymentDateStr[8];
        // strftime(paymentDateStr, sizeof(paymentDateStr), "%Y-%m-%d", (const struct tm*)&cashflow.paymentDate);
        std::cout
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << i
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.endingBalance
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.scheduledPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.unscheduledPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.scheduledPrincipal + cashflow.unscheduledPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.loss
            << std::left << std::setw(WIDTH) << std::setprecision(4) << std::fixed << std::setfill(' ') << cashflow.coupon
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.scheduledPrincipal + cashflow.grossInterest
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.grossInterest
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.netInterest
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.prepayPenalty
            << std::endl;
    }
}