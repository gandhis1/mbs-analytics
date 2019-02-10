#include <algorithm>
#include <iterator>
#include <cmath>

#include "scenario.h"

Scenario::Scenario(double VPR, double CDR, int scenarioLength,
                   VPRType vprType)
    : scenarioLength(scenarioLength), vprType(vprType)
{
    std::fill_n(std::back_inserter(vprVector), scenarioLength, VPR);
    std::fill_n(std::back_inserter(cdrVector), scenarioLength, CDR);
}
