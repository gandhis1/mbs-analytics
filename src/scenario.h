
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
             int scenarioLength = 720,
             VPRType vprType = CPR);
    friend class Engine;

  private:
    std::vector<double> vprVector;
    std::vector<double> cdrVector;
    int scenarioLength;
    VPRType vprType;
};

#endif
