#ifndef SECURITY_H
#define SECURITY_H

#include <map>
#include "group.h"

class Deal
{
protected:
  std::string name;
  std::map<std::string, CollateralGroup> collateral;

public:
  Deal(std::string name) : name(name) {}

  void addLoan(std::string groupId, Loan &loan);

  template <class Iterator>
  void addLoans(std::string groupId, Iterator begin, Iterator end)
  {
    collateral[groupId].addLoans(begin, end);
  }

  unsigned int numberOfLoans() const;

  friend class CashFlowEngine;
};

#endif
