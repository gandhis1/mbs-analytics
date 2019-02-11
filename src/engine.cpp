#include "engine.h"
#include <iostream>

std::map<int, std::map<std::string, double>> CashFlowEngine::runCashflows(
    Pool &pool,
    Scenario &scenario)
{
    std::map<int, std::map<std::string, double>> cashFlows;
    std::cout << scenario.scenarioLength;
    std::cout << pool.id;
    return std::move(cashFlows);
}