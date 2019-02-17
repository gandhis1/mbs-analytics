#include "prepayment_provision.h"

PrepaymentProvision::PrepaymentProvision(PrepaymentProvisionType type, int length) : type(type), length(length) {}
double PrepaymentProvision::calculatePrepaymentPenalty(double voluntaryPrepay)
{
    return getVoluntaryPenaltyRate() * voluntaryPrepay;
}
PrepaymentProvisionType PrepaymentProvision::getType() { return type; }

Lockout::Lockout(int length) : PrepaymentProvision(LOCKOUT, length) { type = LOCKOUT; }
bool Lockout::canVoluntarilyPrepay() { return false; }
double Lockout::getVoluntaryPenaltyRate() { return 0.0; }

Defeasance::Defeasance(int length) : PrepaymentProvision(DEFEASANCE, length) {}
bool Defeasance::canVoluntarilyPrepay() { return false; }
double Defeasance::getVoluntaryPenaltyRate() { return 0.0; }

FixedPenalty::FixedPenalty(int length, double rate) : PrepaymentProvision(FIXED_PENALTY, length), penaltyRate(rate) {}
bool FixedPenalty::canVoluntarilyPrepay() { return true; }
double FixedPenalty::getVoluntaryPenaltyRate() { return penaltyRate; }

YieldMaintenance::YieldMaintenance(int length) : PrepaymentProvision(YIELD_MAINTENANCE, length) {}
bool YieldMaintenance::canVoluntarilyPrepay() { return true; }
double YieldMaintenance::getVoluntaryPenaltyRate() { return 0.0; } // TODO

Open::Open(int length) : PrepaymentProvision(OPEN, length) {}
bool Open::canVoluntarilyPrepay() { return true; }
double Open::getVoluntaryPenaltyRate() { return 0.0; }
