//
// Created by Vijay Vishwakarma on 9/15/19.
//

#include "main.h"
#include "cashflows.h"
#include "scenario.h"
#include "engine.h"

int main(int argc, char** argv) {
    Scenario* scenario = CreateScenario(0.05, 0.01, 0.25, 0, 0.0, 100.0, 100.0);
    CashFlowEngine* engine = CreateEngine();
    Loan* loan = CreateLoan();
    CashFlows cashflows = engine->runCashFlows(*loan, *scenario);
    scenario->prettyPrint();
    cashflows.prettyPrint();
}
