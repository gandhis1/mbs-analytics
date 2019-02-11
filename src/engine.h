#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include "scenario.h"
#include "pool.h"
#include "cashflows.h"

class CashFlowEngine
{
public:
  CashFlows runCashflows(
      Deal &deal,
      Scenario &scenario);
};

#endif