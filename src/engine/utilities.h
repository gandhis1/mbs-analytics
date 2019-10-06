#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>

#include "constants.h"

namespace Utilities
{

    double changeCompoundingBasis(double rate, int origCompoundsPerYear, int newCompoundsPerYear);

    double calculatePayment(double balance, int amortTerm, double periodicRate);

    namespace DateTime
    {

        struct tm createTime(int year, int month, int day);

        struct tm addDateInterval(struct tm date, int years, int months, int days);

        int toYYYYMMDD(struct tm date);

        int daysBetween(struct tm date1, struct tm date2, bool inclusiveEnd = true);

        int monthsBetween(struct tm date1, struct tm date2);

    } // namespace DateTime

} // namespace Utilities

#endif