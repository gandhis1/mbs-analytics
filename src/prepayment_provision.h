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
    virtual bool canVoluntarilyPrepay();
    virtual bool canInvoluntarilyPrepay();
    virtual double calculatePrepaymentPenalty(double voluntaryPrepay, double involuntaryPrepay);
    PrepaymentProvisionType getType();
    template <typename Container>
    static PrepaymentProvision getCurrentPrepaymentProvision(Container& c, int loanAge)
    {
      // TODO: This function is inefficient as it is constantly re-indexing the vector - but works for now
      int cumulativePayments = 0;
      for (unsigned short i = 0; i < c.size(); ++i)
      {
        PrepaymentProvision &provision = c[i];
        if (loanAge > cumulativePayments && loanAge <= cumulativePayments + provision.length)
        {
          return provision;
        }
        else
        {
          cumulativePayments += provision.length;
        }        
      }
      return c.back();
    }
};

class Lockout : public PrepaymentProvision
{
  public:
    Lockout(int length);
    virtual bool canVoluntarilyPrepay();
};

class Defeasance : public PrepaymentProvision
{
  public:
    Defeasance(int length);
    virtual bool canVoluntarilyPrepay();
};

class FixedPenalty : public PrepaymentProvision
{
  protected:
    double penaltyRate;
    virtual double getVoluntaryPenaltyRate();

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