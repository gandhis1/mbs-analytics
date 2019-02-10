
#ifndef SECNARIO_H
#define SCENARIO_H

#include <vector>

enum VPRType
{
  CPR,
  CPY,
  CPJ,
  CPB
};

class Scenario
{
  public:
    Scenario(double vpr = 0.0,
             double cdr = 0.0,
             int ScenarioLength = 540,
             VPRType vprType = CPR);

  private:
    std::vector<double> vprVector;
    std::vector<double> cdrVector;
    int scenarioLength;
    VPRType vprType;
};

#endif
