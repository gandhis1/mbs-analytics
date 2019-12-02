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

Scenario *CreateScenario(double vpr, double cdr, double sev, int lag, double dq, double prinAdv, double intAdv, VPRType vprType, CDRType cdrType)
{
    Scenario *scenario = new Scenario(vpr, cdr, sev, lag, dq, prinAdv, intAdv, vprType, cdrType);
    return scenario;
}
Scenario *CreateVectorScenario(double* vpr, double* cdr, double* sev, int* lag, double* dq, double* prinAdv, double* intAdv, VPRType vprType, CDRType cdrType, int vectorSize)
{
    Scenario *scenario = new Scenario(
        std::vector(vpr, vpr + vectorSize),
        std::vector(cdr, cdr + vectorSize),
        std::vector(sev, sev + vectorSize),
        std::vector(lag, lag + vectorSize),
        std::vector(dq, dq + vectorSize),
        std::vector(prinAdv, prinAdv + vectorSize),
        std::vector(intAdv, intAdv + vectorSize),
        vprType,
        cdrType
    );
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

Loan *CreateLoan(const char *loanId, double originalBalance, double currentBalance, int firstPaymentDateYYYYMMDD, int factorDateYYYYMMDD, int originalLoanTerm, int originalAmortTerm, int originalIOTerm, double grossCoupon, double feeStrip, AccrualBasis accrualBasis, const char *originalPrepaymentString)
{
    auto firstPaymentDate = Utilities::DateTime::fromYYYYMMDD(firstPaymentDateYYYYMMDD);
    auto factorDate = Utilities::DateTime::fromYYYYMMDD(factorDateYYYYMMDD);
    return new Loan(loanId, originalBalance, currentBalance, firstPaymentDate, factorDate, originalLoanTerm, originalAmortTerm, originalIOTerm, grossCoupon, feeStrip, accrualBasis, originalPrepaymentString);
}
void DeleteLoan(Loan *loan)
{
    delete loan;
}
const char *PrettyDescriptionLoan(Loan *loan)
{
    return strdup(loan->prettyDescription().c_str());
}

Deal *CreateDeal(const char *name)
{
    return new Deal(name);
}
void AddLoanToDeal(Deal *deal, Loan *loan, const char *group)
{
    deal->addLoan(group, *loan);
}
void DeleteDeal(Deal *deal)
{
    delete deal;
}

CashFlows *RunCashFlows(CashFlowEngine *engine, Deal* deal, Scenario *scenario)
{
    CashFlows *cashflows = new CashFlows(engine->runCashFlows(*deal, *scenario));
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