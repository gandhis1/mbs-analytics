#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <ctime>

namespace Utilities
{

const double EPSILON = 0.000001;

inline double changeCompoundingBasis(
    double rate, int origCompoundsPerYear, int newCompoundsPerYear)
{
    return 1.0 - pow(1.0 - rate, float(origCompoundsPerYear) / float(newCompoundsPerYear));
}

inline double calculatePayment(double balance, int amortTerm, double periodicRate)
{
    if (amortTerm == 0)
    {
        return periodicRate * balance;
    }
    else
    {
        return balance * periodicRate / (1 - pow(1 + periodicRate, -amortTerm));
    }
}

inline struct tm createTime(int year, int month, int day)
{
    struct tm date;
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    return date;
}

inline struct tm addDateInterval(struct tm date, int years, int months, int days) {
    date.tm_year += years;
    date.tm_mon += months;
    date.tm_mday += days;
    mktime(&date);
    return date;
}

inline int toYYYYMMDD(struct tm date) {
    char date_YYYYMMDD[9];
    strftime(date_YYYYMMDD, 9, "%Y%m%d", &date);
    return std::stoi(date_YYYYMMDD);
}

inline int daysBetween(struct tm date1, struct tm date2)
{
    int secondsBetween = std::difftime(mktime(&date1), mktime(&date2));
    return int(secondsBetween / 60.0 / 24.0);
}

} // namespace Utilities

#endif