#include <algorithm>
#include <iterator>
#include <cmath>

#include "scenario.h"

Scenario::Scenario(double vpr, double cdr, int ScenarioLength,
                   VPRType vprType)
    : scenarioLength(ScenarioLength), vprType(vprType)
{
    std::fill_n(std::back_inserter(vprVector), ScenarioLength, vpr);
    std::fill_n(std::back_inserter(cdrVector), ScenarioLength, cdr);
}
