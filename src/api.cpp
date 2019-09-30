#include <string>

#include "api.h"
#include "cashflows.h"
#include "engine.h"
#include "loan.h"
#include "scenario.h"

CashFlowEngine* CreateEngine()
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


const char* PrettyDescriptionScenario(Scenario* scenario)
{
    return scenario->prettyDescription().c_str();
}

Loan* CreateLoan(const char* loanId, double originalBalance, double currentBalance) //, struct tm factorDate, int originalLoanTerm, int originalAmortTerm, int originalIOTerm, int currentLoanAge, double grossCoupon, double feeStrip, AccrualBasis accrualBasis, const char* originalPrepaymentString)
{
    // std::string loanID = "1717469130";
    // double originalBalance = 763000.00;
    // double currentBalance = 737056.10;
    struct tm factorDate = Utilities::createTime(2019, 2, 1);
    int originalLoanTerm = 60;
    int originalAmortTerm = 360;
    int originalIOTerm = 0;
    int currentLoanAge = 28;
    double grossCoupon = 0.0496;
    double feeStrip = 0.0496 - 0.0248;
    AccrualBasis accrualBasis = ACTUAL_360;
    std::string originalPrepaymentString = "YM(54) O(6)";
    return new Loan(loanId, originalBalance, currentBalance, factorDate, originalLoanTerm, originalAmortTerm, originalIOTerm, currentLoanAge, grossCoupon, feeStrip, accrualBasis, originalPrepaymentString);
}

void DeleteLoan(Loan *loan)
{
    delete loan;
}

const char* PrettyDescriptionLoan(Loan* loan)
{
    return loan->prettyDescription().c_str();
}

CashFlows *RunCashFlows(CashFlowEngine* engine, Loan* loan, Scenario *scenario)
{
    CashFlows* cashflows = new CashFlows(engine->runCashFlows(*loan, *scenario));
    return cashflows;
}

void DeleteCashFlows(CashFlows *cashflows)
{
    delete cashflows;
}

const char* PrettyDescriptionCashFlows(CashFlows* cashflows)
{
    return cashflows->prettyDescription().c_str();
}
