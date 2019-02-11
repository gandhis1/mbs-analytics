#include "group.h"
#include "loan.h"


void CollateralGroup::addLoan(Loan &loan)
{
    loans.push_back(loan);
}