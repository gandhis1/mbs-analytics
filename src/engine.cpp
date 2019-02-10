#include "scenario.h"
#include "engine.h"


std::map<int, std::map<std::string, std::any>> Engine::runCashflows(
    Security &security,
    Scenario &scenario, )
{
    std::map<int, std::map<std::string, std::any>> cashFlows;
        for
            int
                cashFlows[0] = cash
}

double Engine::changeCompoundingBasis(
    double rate, int origCompoundsPerYear, int newCompoundsPerYear)
{
    return 1.0 - pow(1.0 - rate, origCompoundsPerYear / newCompoundsPerYear);
};