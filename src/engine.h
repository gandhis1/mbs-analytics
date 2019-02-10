#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include "scenario.h"
#include "security.h"

class Engine
{
public:
  std::map<int, std::map<std::string, double>> runCashflows(
      Security &security,
      Scenario &scenario);

private:
  double changeCompoundingBasis(double rate,
                                int origCompoundsPerYear = 1,
                                int newCompoundsPerYear = 12);
};

#endif