#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "cashflows.h"
#include "utilities.h"

CashFlow::CashFlow()
    : period(-1), accrualDays(0), endingBalance(0.0), grossCoupon(0.0),
      netCoupon(0.0), grossInterest(0.0), netInterest(0.0), scheduledPrincipal(0.0),
      unscheduledPrincipal(0.0), balloonPrincipal(0.0), recoveryPrincipal(0.0),
      defaultAmount(0.0), realizedLoss(0.0), prepayPenalty(0.0)
{
}

double CashFlow::scheduledPayment()
{
    return scheduledPrincipal + grossInterest;
}

double CashFlow::totalPrincipal()
{
    return scheduledPrincipal + unscheduledPrincipal + balloonPrincipal + recoveryPrincipal;
}

double CashFlow::totalCashflow()
{
    return totalPrincipal() + grossInterest + prepayPenalty;
}

double CashFlow::penaltyRate()
{
    return prepayPenalty / unscheduledPrincipal;
}

std::string CashFlows::prettyDescription()
{
    std::ostringstream textstream;
    const int WIDTH = 17;
    textstream
        << std::left << std::setw(10) << std::setfill(' ') << "Period"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Payment Date"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Accrual Start"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Accrual End"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Accrual Days"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Ending Balance"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Sched Prin"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Unsched Prin"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Balloon Prin"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Recovery Prin"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Total Prin"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Default Amount"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Realized Loss"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Gross Coupon"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Net Coupon"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Sched Payment"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Gross Interest"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Net Interest"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Optimal Gross"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Optimal Net"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Prepay Penalty"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Penalty Rate"
        << std::left << std::setw(WIDTH) << std::setfill(' ') << "Total Cash Flow"
        << std::endl;
    for (auto &cashflow : periodicCashflows)
    {
        textstream
            << std::left << std::setw(10) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.period
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << Utilities::toYYYYMMDD(cashflow.paymentDate)
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << Utilities::toYYYYMMDD(cashflow.accrualStartDate)
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << Utilities::toYYYYMMDD(cashflow.accrualEndDate)
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.accrualDays
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.endingBalance
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.scheduledPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.unscheduledPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.balloonPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.recoveryPrincipal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.totalPrincipal()
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.defaultAmount
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.realizedLoss
            << std::left << std::setw(WIDTH) << std::setprecision(4) << std::fixed << std::setfill(' ') << cashflow.grossCoupon
            << std::left << std::setw(WIDTH) << std::setprecision(4) << std::fixed << std::setfill(' ') << cashflow.netCoupon
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.scheduledPayment()
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.grossInterest
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.netInterest
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.grossInterestOptimal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.netInterestOptimal
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.prepayPenalty
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.penaltyRate()
            << std::left << std::setw(WIDTH) << std::setprecision(2) << std::fixed << std::setfill(' ') << cashflow.totalCashflow()
            << std::endl;
    }
    return textstream.str();
}

void CashFlows::prettyPrint()
{
    std::cout << prettyDescription();
}

double CashFlows::weightedAverageLife(struct tm settleDate)
{
    // TODO: For now do a naive implementation, later on look at settle date and day count
    time_t settleDateTime = mktime(&settleDate);
    long double timePrincipalSumProduct = 0.0;
    long double cumulativePrincipal = 0.0;
    for (auto &periodicCashflow : periodicCashflows)
    {
        // TODO: this is a temporary hack to use the parameter, in reality this is not how settle-date mechanics work
        if (mktime(&periodicCashflow.paymentDate) >= settleDateTime)
        {
            timePrincipalSumProduct += periodicCashflow.totalPrincipal() * periodicCashflow.period / 12.0;
            cumulativePrincipal += periodicCashflow.totalPrincipal();
        }
    }
    return timePrincipalSumProduct / cumulativePrincipal;
}