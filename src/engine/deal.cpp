#include <numeric>

#include "deal.h"

void Deal::addLoan(std::string groupId, Loan &loan)
{
    collateral[groupId].addLoan(loan);
}

unsigned int Deal::numberOfLoans() const
{
    return std::accumulate(
        collateral.begin(),
        collateral.end(),
        0,
        [](int count, std::pair<std::string, CollateralGroup> group) { return count + group.second.loans.size(); });
}
