#include "engine.h"
#include <cmath>
#include <iostream>

std::map<int, std::map<std::string, double>> Engine::runCashflows(
    Security &security,
    Scenario &scenario)
{
    std::map<int, std::map<std::string, double>> cashFlows;
    std::cout << scenario.scenarioLength;
    std::cout << security.id;
    return cashFlows;
}

double Engine::changeCompoundingBasis(
    double rate, int origCompoundsPerYear, int newCompoundsPerYear)
{
    return 1.0 - pow(1.0 - rate, origCompoundsPerYear / newCompoundsPerYear);
}