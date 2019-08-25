#include "cashflows.h"
#include "engine.h"
#include "scenario.h"

extern "C"
{
    __declspec(dllexport) CashFlowEngine *CreateEngine();
    __declspec(dllexport) void DeleteEngine (CashFlowEngine* engine);

    __declspec(dllexport) Scenario *CreateScenario(double vpr, double cdr, double sev, int lag, double dq, double prinAdv, double intAdv);
    __declspec(dllexport) void DeleteScenario (Scenario* scenario);
    __declspec(dllexport) const char* PrettyDescriptionScenario(Scenario *scenario);

    __declspec(dllexport) Loan *CreateLoan();
    __declspec(dllexport) void DeleteLoan (Loan* loan);

    __declspec(dllexport) CashFlows *RunCashFlows(CashFlowEngine* engine, Loan* loan, Scenario *scenario);
    __declspec(dllexport) void DeleteCashFlows (CashFlows* cashflows);
    __declspec(dllexport) const char *PrettyDescriptionCashFlows(CashFlows *cashflows);

}