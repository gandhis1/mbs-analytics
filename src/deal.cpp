#include "deal.h"

void Deal::addLoan(std::string groupId, Loan &loan)
{
    collateral[groupId].addLoan(loan);
}