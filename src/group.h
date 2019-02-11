#ifndef GROUP_H
#define GROUP_H

#include <algorithm>
#include "loan.h"

class CollateralGroup
{
private:
  std::vector<Loan> loans;

public:
  void addLoan(Loan &loan);

  template <class Iterator>
  void addLoans(Iterator begin, Iterator end)
  {
    std::for_each(begin, end, loans.push_back);
  }
};

#endif