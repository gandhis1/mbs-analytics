#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <limits>
#include <map>

namespace Constants
{
const double EPSILON = std::numeric_limits<double>::epsilon();
}

// This enumeration is frequently converted to an integer
// Use traditional weakly-typed enum for implicit conversion
enum PaymentFrequency
{
    MONTHLY = 1,
    QUARTERLY = 3,
    SEMIANNUALLY = 6,
    ANNUALLY = 12
};

enum class AccrualBasis
{
    THIRTY_360,
    ACTUAL_360
};

enum class VPRType
{
    CPR,
    CPY,
    CPP,
    CPJ,
    CPB,
    SMM,
    PSA
};

enum class CDRType
{
    MDR,
    CDR,
    PLD
};

// TODO: Add function overloads for other enumerations in this module
inline std::string enumToString(AccrualBasis enumValue)
{
    std::map<AccrualBasis, const char*> accrualBasisLookup = {
        {AccrualBasis::THIRTY_360, "THIRTY_360"},
        {AccrualBasis::ACTUAL_360, "ACTUAL_360"}};
    return accrualBasisLookup[enumValue];
}

#endif