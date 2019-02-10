#ifndef POOL_H
#define POOL_H

#include <algorithm>
#include <string>
#include <vector>
#include "loan.h"

class Pool
{
  private:
    std::string id;
    std::vector<Loan> loans;

  public:
    Pool(std::string id);

    template <typename container>
    Pool(std::string id, container& c)
    {
        for (auto &loan : c)
        {
            loans.push_back(loan);
        }
    }

    template <typename iterator>
    Pool(std::string id, iterator begin, iterator end)
    {
        std::for_each(begin, end, loans.push_back);
    }

    static Pool from_identifier(std::string identifier) {
      Pool pool(identifier);
      return pool;
    }

    friend class Engine;
};

#endif
