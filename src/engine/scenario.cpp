#include <algorithm>
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>

#include "constants.h"
#include "scenario.h"

// Single-value scalar constructor
Scenario::Scenario(double vpr,
                   double cdr,
                   double sev,
                   int lag,
                   double dq,
                   double prinAdv,
                   double intAdv,
                   VPRType vprType,
                   CDRType cdrType,
                   bool extendLagsPastMaturity)
    : vprType(vprType), cdrType(cdrType), extendLagsPastMaturity(extendLagsPastMaturity)
{
    std::fill_n(std::back_inserter(vprVector), MAX_PERIODS, vpr);
    std::fill_n(std::back_inserter(cdrVector), MAX_PERIODS, cdr);
    std::fill_n(std::back_inserter(sevVector), MAX_PERIODS, sev);
    std::fill_n(std::back_inserter(lagVector), MAX_PERIODS, lag);
    std::fill_n(std::back_inserter(dqVector), MAX_PERIODS, dq);
    std::fill_n(std::back_inserter(prinAdvVector), MAX_PERIODS, prinAdv);
    std::fill_n(std::back_inserter(intAdvVector), MAX_PERIODS, intAdv);
}

// Full vector inputs
Scenario::Scenario(std::vector<double> vprVector,
                   std::vector<double> cdrVector,
                   std::vector<double> sevVector,
                   std::vector<int> lagVector,
                   std::vector<double> dqVector,
                   std::vector<double> prinAdvVector,
                   std::vector<double> intAdvVector,
                   VPRType vprType,
                   CDRType cdrType,
                   bool extendLagsPastMaturity)
    : vprVector(vprVector), cdrVector(cdrVector), sevVector(sevVector),
      lagVector(lagVector), dqVector(dqVector), prinAdvVector(prinAdvVector),
      intAdvVector(intAdvVector), vprType(vprType), cdrType(cdrType),
      extendLagsPastMaturity(extendLagsPastMaturity)
{
}

std::string Scenario::prettyDescription()
{
    std::string vprVectorSummary = summarizeAssumptionVector(vprVector);
    std::string cdrVectorSummary = summarizeAssumptionVector(cdrVector);
    std::string sevVectorSummary = summarizeAssumptionVector(sevVector);
    std::string lagVectorSummary = summarizeAssumptionVector(lagVector);
    std::string dqVectorSummary = summarizeAssumptionVector(dqVector);
    std::string prinAdvVectorSummary = summarizeAssumptionVector(prinAdvVector);
    std::string intAdvVectorSummary = summarizeAssumptionVector(intAdvVector);
    std::vector<unsigned long long> summaryLengths = {
        vprVectorSummary.size(), cdrVectorSummary.size(), sevVectorSummary.size(),
        lagVectorSummary.size(), dqVectorSummary.size(), prinAdvVectorSummary.size(),
        intAdvVectorSummary.size()
    };
    size_t longestDescriptionSize = *std::max_element(summaryLengths.begin(), summaryLengths.end());
    std::string border = std::string(longestDescriptionSize + 15, '*');
    std::ostringstream textstream;
    textstream
        << border << std::endl
        << std::left << std::setw(10) << "VPR: " << std::setw(longestDescriptionSize) << vprVectorSummary + " " + enumToString(vprType) << std::endl
        << std::left << std::setw(10) << "CDR: " << std::setw(longestDescriptionSize) << cdrVectorSummary + " " + enumToString(cdrType) << std::endl
        << std::left << std::setw(10) << "SEV: " << std::setw(longestDescriptionSize) << sevVectorSummary << std::endl
        << std::left << std::setw(10) << "LAG: " << std::setw(longestDescriptionSize) << lagVectorSummary << std::endl
        << std::left << std::setw(10) << "DQ: " << std::setw(longestDescriptionSize) << dqVectorSummary << std::endl
        << std::left << std::setw(10) << "ADV PRIN: " << std::setw(longestDescriptionSize) << intAdvVectorSummary << std::endl
        << std::left << std::setw(10) << "ADV INT: " << std::setw(longestDescriptionSize) << prinAdvVectorSummary << std::endl
        << std::left << std::setw(10) << "EXTEND: " << std::setw(longestDescriptionSize) << (extendLagsPastMaturity ? "TRUE" : "FALSE") << std::endl
        << border << std::endl;
    return textstream.str();
}

void Scenario::prettyPrint()
{
    std::cout << prettyDescription();
}