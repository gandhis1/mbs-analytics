
#ifndef SCENARIO_H
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
           double sev = 0.0,
           int lag = 0,
           double dq = 0.0,
           double adv = 0.0,
           int scenarioLength = 720,
           VPRType vprType = CPR);
  Scenario(std::vector<double> vprVector,
           std::vector<double> cdrVector,
           std::vector<double> sevVector,
           std::vector<int> lagVector,
           std::vector<double> dqVector,
           std::vector<double> advVector,
           int ScenarioLength,
           VPRType vprType);
  friend class CashFlowEngine;

private:
  std::vector<double> vprVector;
  std::vector<double> cdrVector;
  std::vector<double> sevVector;
  std::vector<int> lagVector;
  std::vector<double> dqVector;
  std::vector<double> advVector;
  int scenarioLength;
  VPRType vprType;
};

#endif
