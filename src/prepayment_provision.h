#ifndef PREPAYMENT_PROVISION_H
#define PREPAYMENT_PROVISION_H

#include <cctype>
#include <iostream>
#include <memory>
#include <vector>

enum PrepaymentProvisionType
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
    virtual double getVoluntaryPenaltyRate() = 0;

public:
    PrepaymentProvision(PrepaymentProvisionType type, int length);
    
    virtual bool canVoluntarilyPrepay() = 0;
    virtual std::string summarize() = 0;
    double calculatePrepaymentPenalty(double voluntaryPrepay);
    PrepaymentProvisionType getType();
    int getLength();
    template <typename Container>
    static std::shared_ptr<PrepaymentProvision> getCurrentPrepaymentProvision(Container &container, int loanAge)
    {
        // TODO: This function is inefficient as it is constantly re-indexing the vector - but works for now
        int cumulativePayments = 0;
        for (unsigned short i = 0; i < container.size(); ++i)
        {
            if (loanAge > cumulativePayments && loanAge <= cumulativePayments + container[i]->length)
            {
                return container[i];
            }
            else
            {
                cumulativePayments += container[i]->length;
            }
        }
        return container.back();
    }
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

std::vector<std::shared_ptr<PrepaymentProvision>> parsePrepaymentString(std::string);

#endif