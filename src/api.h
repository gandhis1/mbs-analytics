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
    EXPORT void DeleteEngine (CashFlowEngine* engine);

    EXPORT Scenario *CreateScenario(double vpr, double cdr, double sev, int lag, double dq, double prinAdv, double intAdv);
    EXPORT void DeleteScenario (Scenario* scenario);
    EXPORT const char* PrettyDescriptionScenario(Scenario *scenario);

    EXPORT Loan *CreateLoan(const char *loanId, double originalBalance, double currentBalance); //, struct tm factorDate, int originalLoanTerm, int originalAmortTerm, int originalIOTerm, int currentLoanAge, double grossCoupon, double feeStrip, AccrualBasis accrualBasis, const char* originalPrepaymentString);
    EXPORT void DeleteLoan (Loan* loan);
    EXPORT const char *PrettyDescriptionLoan(Loan *loan);

    EXPORT CashFlows *RunCashFlows(CashFlowEngine* engine, Loan* loan, Scenario *scenario);
    EXPORT void DeleteCashFlows (CashFlows* cashflows);
    EXPORT const char *PrettyDescriptionCashFlows(CashFlows *cashflows);

}