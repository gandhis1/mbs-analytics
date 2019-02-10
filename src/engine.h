#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include "scenario.h"
#include "pool.h"

class Engine
{
public:
  std::map<int, std::map<std::string, double>> runCashflows(
      Pool &pool,
      Scenario &scenario);
};

#endif