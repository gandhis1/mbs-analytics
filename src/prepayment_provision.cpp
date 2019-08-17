#include "loan.h"
#include "prepayment_provision.h"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <sstream>

PrepaymentProvision::PrepaymentProvision(PrepaymentProvisionType type, int length) : type(type), length(length) {}
double PrepaymentProvision::calculatePrepaymentPenalty(const Loan& loan, int period, double voluntaryPrepay)
{
    return getVoluntaryPenaltyRate(loan, period) * voluntaryPrepay;
}
double PrepaymentProvision::getVoluntaryPenaltyRate(const Loan& loan, int period) {
    // By default paramters unused, so silence compiler warning
    // However sub-classes for yield and spread maintenance will override this
    (void)loan;
    (void)period; 
    return getVoluntaryPenaltyRate();
}
PrepaymentProvisionType PrepaymentProvision::getType() { return type; }

int PrepaymentProvision::getLength() { return length; }

Lockout::Lockout(int length) : PrepaymentProvision(LOCKOUT, length) { type = LOCKOUT; }
std::string Lockout::summarize() { return "L(" + std::to_string(length) + ")"; }
bool Lockout::canVoluntarilyPrepay() { return false; }
double Lockout::getVoluntaryPenaltyRate() { return 0.0; }

Defeasance::Defeasance(int length) : PrepaymentProvision(DEFEASANCE, length) {}
std::string Defeasance::summarize() { return "D(" + std::to_string(length) + ")"; }
bool Defeasance::canVoluntarilyPrepay() { return false; }
double Defeasance::getVoluntaryPenaltyRate() { return 0.0; }

FixedPenalty::FixedPenalty(int length, double rate) : PrepaymentProvision(FIXED_PENALTY, length), penaltyRate(rate) {}
std::string FixedPenalty::summarize()
{
    std::ostringstream summary;
    summary << penaltyRate * 100.0 << "(" << length << ")";
    return summary.str();
}
bool FixedPenalty::canVoluntarilyPrepay() { return true; }
double FixedPenalty::getVoluntaryPenaltyRate() { return penaltyRate; }

YieldMaintenance::YieldMaintenance(int length) : PrepaymentProvision(YIELD_MAINTENANCE, length) {}
std::string YieldMaintenance::summarize() { return "YM(" + std::to_string(length) + ")"; }
bool YieldMaintenance::canVoluntarilyPrepay() { return true; }
double YieldMaintenance::getVoluntaryPenaltyRate() {
    return 0.0;
}

Open::Open(int length) : PrepaymentProvision(OPEN, length) {}
std::string Open::summarize() { return "O(" + std::to_string(length) + ")"; }
bool Open::canVoluntarilyPrepay() { return true; }
double Open::getVoluntaryPenaltyRate() { return 0.0; }

std::string summarizePrepaymentProvisions(std::vector<std::shared_ptr<PrepaymentProvision>> prepaymentProvisions)
{
    return std::accumulate(prepaymentProvisions.begin(), prepaymentProvisions.end(), std::string(), [](std::string a, auto b) { return a + (a.empty() ? "" : " ") + b->summarize(); });
}

std::vector<std::shared_ptr<PrepaymentProvision>> parsePrepaymentString(std::string prepaymentString)
{
    // An (unrealistic) example string to be parsed would be: "L(24) YM(14) D(12) 1%(6) O(4)"
    // First tokenize the string
    std::vector<std::string> tokens;
    std::string currentToken = "";
    for (auto it = prepaymentString.begin(); it != prepaymentString.end(); ++it)
    {
        switch (*it)
        {
        case 'Y':
            currentToken += *it;
            break;
        case 'L':
        case 'D':
        case 'O':
        case 'M': // Second letter of YM
            currentToken += *it;
        case '(':
        case ')':
        case ' ':
            if (currentToken != "")
            {
                tokens.push_back(currentToken);
                currentToken = "";
            }
            break;
        case '%':
            break; // Do nothing
        default:
            if (isdigit(*it))
            {
                currentToken += *it;
            }
            else
            {
                throw std::invalid_argument("Prepayment string is malformed: " + prepaymentString);
            }
        }
    }

    // Then translate the tokens into actual objects
    std::vector<std::shared_ptr<PrepaymentProvision>> prepaymentProvisions;
    for (unsigned int i = 0; i < tokens.size() - 1; i += 2)
    {
        std::string provision = tokens[i];
        int length = std::stoi(tokens[i + 1]);
        std::shared_ptr<PrepaymentProvision> prepaymentProvision;
        if (std::all_of(provision.begin(), provision.end(), isdigit))
        {
            prepaymentProvision = std::make_shared<FixedPenalty>(length, std::stof(provision) / 100.0);
        }
        else if (provision == "L")
        {
            prepaymentProvision = std::make_shared<Lockout>(length);
        }
        else if (provision == "D")
        {
            prepaymentProvision = std::make_shared<Defeasance>(length);
        }
        else if (provision == "YM")
        {
            prepaymentProvision = std::make_shared<YieldMaintenance>(length);
        }
        else if (provision == "O")
        {
            prepaymentProvision = std::make_shared<Open>(length);
        }
        prepaymentProvisions.push_back(prepaymentProvision);
    }
    // In the future this should be removed as multiple and/or imperfect input formats are allowed
    assert(prepaymentString == summarizePrepaymentProvisions(prepaymentProvisions));
    return prepaymentProvisions;
}
