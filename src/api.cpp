#include <string>
#include <cstring>

#include "api.h"
#include "cashflows.h"
#include "engine.h"
#include "loan.h"
#include "scenario.h"

CashFlowEngine *CreateEngine()
{
    return new CashFlowEngine();
}

void DeleteEngine(CashFlowEngine *engine)
{
    delete engine;
}

Scenario *CreateScenario(double vpr, double cdr, double sev, int lag, double dq, double prinAdv, double intAdv)
{
    Scenario *scenario = new Scenario(vpr, cdr, sev, lag, dq, prinAdv, intAdv);
    return scenario;
}

void DeleteScenario(Scenario *scenario)
{
    delete scenario;
}

const char *PrettyDescriptionScenario(Scenario *scenario)
{
    return strdup(scenario->prettyDescription().c_str());
}

Loan *CreateLoan(const char *loanId, double originalBalance, double currentBalance, struct tm factorDate, int originalLoanTerm, int originalAmortTerm, int originalIOTerm, int currentLoanAge, double grossCoupon, double feeStrip, AccrualBasis accrualBasis, const char* originalPrepaymentString)
{
    return new Loan(loanId, originalBalance, currentBalance, factorDate, originalLoanTerm, originalAmortTerm, originalIOTerm, currentLoanAge, grossCoupon, feeStrip, accrualBasis, originalPrepaymentString);
}

void DeleteLoan(Loan *loan)
{
    delete loan;
}

const char *PrettyDescriptionLoan(Loan *loan)
{
    return strdup(loan->prettyDescription().c_str());
}

CashFlows *RunCashFlows(CashFlowEngine *engine, Loan *loan, Scenario *scenario)
{
    CashFlows *cashflows = new CashFlows(engine->runCashFlows(*loan, *scenario));
    return cashflows;
}

void DeleteCashFlows(CashFlows *cashflows)
{
    delete cashflows;
}

const char *PrettyDescriptionCashFlows(CashFlows *cashflows)
{
    return strdup(cashflows->prettyDescription().c_str());
}

char *strdup(const char *cStr)
{
    // WARNING: This can create a memory leak as one still needs to free()
    // It is fairly harmless to leak this small amount, as the various pretty
    // print functions are really only used for contextual debugging pruposes
    char *cStrCopy = (char *)malloc(sizeof(*cStr) * (strlen(cStr) + 1));
    return strcpy(cStrCopy, cStr);
}