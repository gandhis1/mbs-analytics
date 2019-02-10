#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>

namespace Utilities
{

double changeCompoundingBasis(
    double rate, int origCompoundsPerYear, int newCompoundsPerYear)
{
    return 1.0 - pow(1.0 - rate, origCompoundsPerYear / newCompoundsPerYear);
}

double calculatePayment(double balance, int amortTerm, double rate)
{
    return balance * rate / (1 - pow(1 + rate, -amortTerm));
}

} // namespace Utilities

#endif