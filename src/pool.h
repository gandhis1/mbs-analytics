#ifndef POOL_H
#define POOL_H

#include <algorithm>
#include <string>
#include <type_traits>
#include <vector>
#include "loan.h"
#include "group.h"
#include "deal.h"

class Pool : public Deal
{
public:
  Pool(std::string name): Deal(name) {}

  void addLoan(Loan &loan)
  {
    Deal::addLoan("all", loan);
  }

  template <class Iterator>
  void addLoans(Iterator begin, Iterator end)
  {
    Deal::addLoans(begin, end);
  }
};

#endif
