#ifndef PREPAYMENT_PROVISION_H
#define PREPAYMENT_PROVISION_H

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
    virtual double getVoluntaryPenaltyRate();
    virtual double getInvoluntaryPenaltyRate();

  public:
    PrepaymentProvision(PrepaymentProvisionType type, int length);
    virtual bool canVoluntaryPrepay();
    virtual bool canInvoluntaryPrepay();
    virtual double calculatePrepaymentPenalty(double voluntaryPrepay, double involuntaryPrepay);
    PrepaymentProvisionType getType();
};

class Lockout : public PrepaymentProvision
{
  public:
    Lockout(int length);
    bool canVoluntaryPrepay();
};

class Defeasance : public PrepaymentProvision
{
  public:
    Defeasance(int length);
    virtual bool canVoluntaryPrepay();
};

class FixedPenalty : public PrepaymentProvision
{
  protected:
    double penalty_rate;

  public:
    FixedPenalty(int length, double rate);
};

class YieldMaintenance : public PrepaymentProvision
{
  public:
    YieldMaintenance(int length);
};

class Open : public PrepaymentProvision
{
  public:
    Open(int length);
};

#endif