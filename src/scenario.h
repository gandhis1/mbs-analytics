
#ifndef SCENARIO_H
#define SCENARIO_H

#include <vector>
#include "constants.h"
#include "utilities.h"

class Scenario
{
public:
  Scenario(double vpr = 0.0,
           double cdr = 0.0,
           double sev = 0.0,
           int lag = 0,
           double dq = 0.0,
           double prinAdv = 100.0,
           double intAdv = 100.0,
           VPRType vprType = VPRType::CPR,
           bool extendLagsPastMaturity = true);
  Scenario(std::vector<double> vprVector,
           std::vector<double> cdrVector,
           std::vector<double> sevVector,
           std::vector<int> lagVector,
           std::vector<double> dqVector,
           std::vector<double> prinAdvVector,
           std::vector<double> intAdvVector,
           VPRType vprType = VPRType::CPR,
           bool extendLagsPastMaturity = true);
  std::string prettyDescription();
  void prettyPrint();
  friend class CashFlowEngine;

private:
  unsigned short MAX_PERIODS = 720;
  std::vector<double> vprVector;
  std::vector<double> cdrVector;
  std::vector<double> sevVector;
  std::vector<int> lagVector;
  std::vector<double> dqVector;
  std::vector<double> prinAdvVector;
  std::vector<double> intAdvVector;
  VPRType vprType;
  bool extendLagsPastMaturity;
  template <typename T>
  std::string summarizeAssumptionVector(std::vector<T> &assumptions)
  {
    // Adjust decimals to whole numbers (assume percentage) and
    // floating-point integers to actual integers (avoid trailing zeroes)
    auto const &formatAssumption = [](T value) -> std::string {
      T retVal = value < 1.0 ? round(value * 10000.0) / 100.0 : value;
      if (abs(float(int(retVal)) - float(retVal)) <= Constants::EPSILON)
      {
        return std::to_string(int(retVal));
      }
      else {
        return std::to_string(retVal);
      }
    };
    std::vector<std::pair<T, unsigned short>> assumptionCounts;
    for (const T &value : assumptions)
    {
      auto assumptionCount = --assumptionCounts.end();
      if (assumptionCounts.size() > 0 && assumptionCount->first == value)
      {
        ++assumptionCount->second;
      }
      else
      {
        assumptionCounts.emplace_back(std::make_pair(value, 1));
      }
    }
    if (assumptionCounts.size() == 1)
    {
      T assumptionValue = assumptionCounts[0].first;
      return formatAssumption(assumptionValue);
    }
    else
    {
      std::string assumptionSummary = "";
      for (auto assumptionCount : assumptionCounts)
      {
        auto delim = assumptionSummary.empty() ? "" : " ";
        assumptionSummary += (delim + formatAssumption(assumptionCount.first) + " FOR " + std::to_string(assumptionCount.second));
      }
      return assumptionSummary;
    }
  }
};

#endif
