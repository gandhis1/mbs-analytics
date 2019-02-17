#include "prepayment_provision.h"

PrepaymentProvision::PrepaymentProvision(PrepaymentProvisionType type, int length) : type(type), length(length) {}
double PrepaymentProvision::getVoluntaryPenaltyRate() { return 0.0; }
double PrepaymentProvision::getInvoluntaryPenaltyRate() { return 0.0; }
bool PrepaymentProvision::canVoluntarilyPrepay() { return true; }
bool PrepaymentProvision::canInvoluntarilyPrepay() { return true; }
double PrepaymentProvision::calculatePrepaymentPenalty(double voluntaryPrepay, double involuntaryPrepay)
{
    return getVoluntaryPenaltyRate() * voluntaryPrepay + getInvoluntaryPenaltyRate() * involuntaryPrepay;
}
PrepaymentProvisionType PrepaymentProvision::getType() { return type; }

Lockout::Lockout(int length) : PrepaymentProvision(LOCKOUT, length) { type = LOCKOUT; }
bool Lockout::canVoluntarilyPrepay() { return false; }

Defeasance::Defeasance(int length) : PrepaymentProvision(DEFEASANCE, length) {}
bool Defeasance::canVoluntarilyPrepay() { return false; }

FixedPenalty::FixedPenalty(int length, double rate) : PrepaymentProvision(FIXED_PENALTY, length), penaltyRate(rate) {}
double FixedPenalty::getVoluntaryPenaltyRate() { return penaltyRate; }

YieldMaintenance::YieldMaintenance(int length) : PrepaymentProvision(YIELD_MAINTENANCE, length) {}

Open::Open(int length) : PrepaymentProvision(OPEN, length) {}
