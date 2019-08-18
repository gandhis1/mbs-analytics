#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include "scenario.h"
#include "pool.h"
#include "cashflows.h"

class CashFlowEngine
{
public:
  CashFlows runCashflows(const Deal &deal, const Scenario &scenario);
  CashFlows amortizeLoan(const Loan &loan, const Scenario &scenario);
};

#endif