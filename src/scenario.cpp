#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>

#include "scenario.h"

// Single-value scalar constructor
Scenario::Scenario(double vpr,
                   double cdr,
                   double sev,
                   int lag,
                   double dq,
                   double adv,
                   VPRType vprType,
                   bool extendLagsPastMaturity)
    : vprType(vprType), extendLagsPastMaturity(extendLagsPastMaturity)
{
    std::fill_n(std::back_inserter(vprVector), MAX_PERIODS, vpr);
    std::fill_n(std::back_inserter(cdrVector), MAX_PERIODS, cdr);
    std::fill_n(std::back_inserter(sevVector), MAX_PERIODS, sev);
    std::fill_n(std::back_inserter(lagVector), MAX_PERIODS, lag);
    std::fill_n(std::back_inserter(dqVector), MAX_PERIODS, dq);
    std::fill_n(std::back_inserter(advVector), MAX_PERIODS, adv);
}

// Full vector inputs
Scenario::Scenario(std::vector<double> vprVector,
                   std::vector<double> cdrVector,
                   std::vector<double> sevVector,
                   std::vector<int> lagVector,
                   std::vector<double> dqVector,
                   std::vector<double> advVector,
                   VPRType vprType,
                   bool extendLagsPastMaturity)
    : vprVector(vprVector), cdrVector(cdrVector), sevVector(sevVector),
      lagVector(lagVector), dqVector(dqVector), advVector(advVector),
      vprType(vprType), extendLagsPastMaturity(extendLagsPastMaturity)
{
}

void Scenario::prettyPrint()
{
    std::string vprVectorSummary = summarizeAssumptionVector(vprVector);
    std::string cdrVectorSummary = summarizeAssumptionVector(cdrVector);
    std::string sevVectorSummary = summarizeAssumptionVector(sevVector);
    std::string lagVectorSummary = summarizeAssumptionVector(lagVector);
    std::string dqVectorSummary = summarizeAssumptionVector(dqVector);
    std::string advVectorSummary = summarizeAssumptionVector(advVector);
    std::vector<unsigned long long> summaryLengths = {
        vprVectorSummary.size(), cdrVectorSummary.size(), sevVectorSummary.size(),
        lagVectorSummary.size(), dqVectorSummary.size(), advVectorSummary.size()};
    size_t longestDescriptionSize = *std::max_element(summaryLengths.begin(), summaryLengths.end());
    std::string border = std::string(longestDescriptionSize + 15, '*');
    std::cout
        << std::endl
        << border << std::endl
        << std::left << std::setw(10) << "VPR: " << std::setw(longestDescriptionSize) << vprVectorSummary << std::endl
        << std::left << std::setw(10) << "CDR: " << std::setw(longestDescriptionSize) << cdrVectorSummary << std::endl
        << std::left << std::setw(10) << "SEV: " << std::setw(longestDescriptionSize) << sevVectorSummary << std::endl
        << std::left << std::setw(10) << "LAG: " << std::setw(longestDescriptionSize) << lagVectorSummary << std::endl
        << std::left << std::setw(10) << "DQ: " << std::setw(longestDescriptionSize) << dqVectorSummary << std::endl
        << std::left << std::setw(10) << "ADV: " << std::setw(longestDescriptionSize) << advVectorSummary << std::endl
        << std::left << std::setw(10) << "EXTEND: " << std::setw(longestDescriptionSize) << (extendLagsPastMaturity ? "TRUE": "FALSE") << std::endl
        << border << std::endl
        << std::endl;
}
