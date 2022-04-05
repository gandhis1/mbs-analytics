#ifndef API_H
#define API_H

#include "cashflows.h"
#include "engine.h"
#include "scenario.h"

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C"
{
    EXPORT CashFlowEngine *CreateEngine();
    EXPORT void DeleteEngine(CashFlowEngine *engine);

    EXPORT Scenario *CreateScenario(double vpr, double cdr, double sev, int lag, double dq, double prinAdv, double intAdv, VPRType vprType, CDRType cdrType);
    EXPORT Scenario *CreateVectorScenario(double* vpr, double* cdr, double* sev, int* lag, double* dq, double* prinAdv, double* intAdv, VPRType vprType, CDRType cdrType, int vectorSize);
    EXPORT void DeleteScenario(Scenario *scenario);
    EXPORT const char *PrettyDescriptionScenario(Scenario *scenario);

    EXPORT Loan *CreateLoan(const char *loanId, double originalBalance, double currentBalance, int firstPaymentDateYYYYMMDD, int factorDateYYYYMMDD, int originalLoanTerm, int originalAmortTerm, int originalIOTerm, double grossCoupon, double feeStrip, AccrualBasis accrualBasis, const char *originalPrepaymentString);
    EXPORT void DeleteLoan(Loan *loan);
    EXPORT const char *PrettyDescriptionLoan(Loan *loan);

    EXPORT Deal *CreateDeal(const char *name);
    EXPORT void AddLoanToDeal(Deal *deal, Loan *loan, const char *group);
    EXPORT void DeleteDeal(Deal *deal);

    EXPORT CashFlows *RunCashFlows(CashFlowEngine *engine, Deal *deal, Scenario *scenario);
    EXPORT void DeleteCashFlows(CashFlows *cashflows);
    EXPORT const char *PrettyDescriptionCashFlows(CashFlows *cashflows, bool detailed);
}

#endif