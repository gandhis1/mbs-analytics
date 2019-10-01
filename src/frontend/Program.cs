using System;

namespace frontend
{
    class Program

    {
        static void Main(string[] args)
        {
            Scenario scenario = new Scenario(
                vpr: 0.05,
                cdr: 0.01,
                sev: 0.25,
                lag: 0,
                dq: 0.0,
                prinAdv: 100.0,
                intAdv: 100.0
            );
            CashFlowEngine engine = new CashFlowEngine();
            Loan loan = new Loan(
                loanId: "1717469130",
                originalBalance: 763000.0,
                currentBalance: 763000.0,
                factorDate: new DateTime(2019, 2, 1),
                originalLoanTerm: 60,
                originalAmortTerm: 360,
                originalIOTerm: 0,
                currentLoanAge: 28,
                grossCoupon: 0.0496,
                feeStrip: 0.0248,
                accrualBasis: AccrualBasis.ACTUAL_360,
                originalPrepaymentString: "YM(54) O(6)"
            );
            CashFlows cashflows = engine.RunCashFlows(loan, scenario);
            scenario.PrettyPrint();
            loan.PrettyPrint();
            cashflows.PrettyPrint();
        }
    }
}
