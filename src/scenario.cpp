#include <algorithm>
#include <cmath>
#include <iterator>
#include <vector>

#include "scenario.h"

// Single-value scalar constructor
Scenario::Scenario(double vpr, double cdr, double sev, int lag,
                   double dq, double adv, int ScenarioLength, VPRType vprType,
                   bool extendLagsPastMaturity)
    : scenarioLength(ScenarioLength), vprType(vprType),
      extendLagsPastMaturity(extendLagsPastMaturity)
{
    std::fill_n(std::back_inserter(vprVector), ScenarioLength, vpr);
    std::fill_n(std::back_inserter(cdrVector), ScenarioLength, cdr);
    std::fill_n(std::back_inserter(sevVector), ScenarioLength, sev);
    std::fill_n(std::back_inserter(lagVector), ScenarioLength, lag);
    std::fill_n(std::back_inserter(dqVector), ScenarioLength, dq);
    std::fill_n(std::back_inserter(advVector), ScenarioLength, adv);
}

// Full vector inputs
Scenario::Scenario(std::vector<double> vprVector,
                   std::vector<double> cdrVector,
                   std::vector<double> sevVector,
                   std::vector<int> lagVector,
                   std::vector<double> dqVector,
                   std::vector<double> advVector,
                   int ScenarioLength,
                   VPRType vprType,
                   bool extendLagsPastMaturity)
    : vprVector(vprVector), cdrVector(cdrVector), sevVector(sevVector),
      lagVector(lagVector), dqVector(dqVector), advVector(advVector),
      scenarioLength(ScenarioLength), vprType(vprType),
      extendLagsPastMaturity(extendLagsPastMaturity)
{
}