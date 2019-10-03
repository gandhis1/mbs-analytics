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
    SMM,
    CPR,
    CPY,
    CPP,
    CPJ,
    CPB,
    PSA
};

enum class CDRType
{
    MDR,
    CDR,
    PLD
};

inline std::string enumToString(PaymentFrequency enumValue)
{
    std::map<PaymentFrequency, const char*> lookup = {
        {PaymentFrequency::MONTHLY, "MONTHLY"},
        {PaymentFrequency::QUARTERLY, "QUARTERLY"},
        {PaymentFrequency::SEMIANNUALLY, "SEMIANNUALLY"},
        {PaymentFrequency::ANNUALLY, "ANNUALLY"}
    };
    return lookup[enumValue];
}

inline std::string enumToString(AccrualBasis enumValue)
{
    std::map<AccrualBasis, const char*> lookup = {
        {AccrualBasis::THIRTY_360, "THIRTY_360"},
        {AccrualBasis::ACTUAL_360, "ACTUAL_360"}
    };
    return lookup[enumValue];
}

inline std::string enumToString(VPRType enumValue)
{
    std::map<VPRType, const char*> lookup = {
        {VPRType::SMM, "SMM"},
        {VPRType::CPR, "CPR"},
        {VPRType::CPY, "CPY"},
        {VPRType::CPP, "CPP"},
        {VPRType::CPJ, "CPJ"},
        {VPRType::CPB, "CPB"},
        {VPRType::PSA, "PSA"}
    };
    return lookup[enumValue];
}

inline std::string enumToString(CDRType enumValue)
{
    std::map<CDRType, const char*> lookup = {
        {CDRType::MDR, "MDR"},
        {CDRType::CDR, "CDR"},
        {CDRType::PLD, "PLD"}
    };
    return lookup[enumValue];
}

#endif