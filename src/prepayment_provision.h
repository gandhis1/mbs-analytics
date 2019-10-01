#ifndef PREPAYMENT_PROVISION_H
#define PREPAYMENT_PROVISION_H

#include <cctype>
#include <iostream>
#include <memory>
#include <vector>

class Loan;  // Forward declaration to avoid circular header imports

enum class PrepaymentProvisionType
{
    LOCKOUT,
    DEFEASANCE,
    FIXED_PENALTY,
    YIELD_MAINTENANCE,
    OPEN
};

class PrepaymentProvision
{
protected:
    PrepaymentProvisionType type;
    int length;
    virtual double getVoluntaryPenaltyRate(const Loan& loan, int period);
    virtual double getVoluntaryPenaltyRate() = 0;

public:
    PrepaymentProvision(PrepaymentProvisionType type, int length);

    friend class Loan;

    virtual bool canVoluntarilyPrepay() = 0;
    virtual std::string summarize() = 0;
    double calculatePrepaymentPenalty(const Loan &loan, int period, double voluntaryPrepay);
    PrepaymentProvisionType getType();
    int getLength();
};

class Lockout : public PrepaymentProvision
{
protected:
    double getVoluntaryPenaltyRate() override;

public:
    Lockout(int length);
    std::string summarize() override;
    bool canVoluntarilyPrepay() override;
};

class Defeasance : public PrepaymentProvision
{
protected:
    double getVoluntaryPenaltyRate() override;

public:
    Defeasance(int length);
    std::string summarize() override;
    bool canVoluntarilyPrepay() override;
};

class FixedPenalty : public PrepaymentProvision
{
protected:
    double penaltyRate;
    double getVoluntaryPenaltyRate() override;

public:
    FixedPenalty(int length, double rate);
    std::string summarize() override;
    bool canVoluntarilyPrepay() override;
};

class YieldMaintenance : public PrepaymentProvision
{
protected:
    double getVoluntaryPenaltyRate() override;

public:
    YieldMaintenance(int length);
    std::string summarize() override;
    bool canVoluntarilyPrepay() override;
};

class Open : public PrepaymentProvision
{
protected:
    double getVoluntaryPenaltyRate() override;

public:
    Open(int length);
    std::string summarize() override;
    bool canVoluntarilyPrepay() override;
};

std::string summarizePrepaymentProvisions(std::vector<std::shared_ptr<PrepaymentProvision>>);
std::vector<std::shared_ptr<PrepaymentProvision>> parsePrepaymentString(std::string);

#endif