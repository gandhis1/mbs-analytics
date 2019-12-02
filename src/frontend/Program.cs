using System;

namespace frontend
{
    class Program

    {
        static void Main(string[] args)
        {
            var deal = new Deal("Example Deal");
            var scenario = new Scenario(
                vpr: new [] {0.0},
                cdr: new [] {0.12682503013, 0},
                sev: new [] {0.5},
                lag: new [] {6},
                dq: new [] {0.0},
                prinAdv: new [] {1.0},
                intAdv: new [] {1.0}
            );
            Loan loan = new Loan(
                loanId: "Example Loan",
                originalBalance: 1_000_000.0,
                currentBalance: 1_000_000.0,
                firstPaymentDate: new DateTime(2019, 1, 1),
                factorDate: new DateTime(2019, 1, 1),
                originalLoanTerm: 120,
                originalAmortTerm: 120,
                originalIOTerm: 0,
                grossCoupon: 0.06,
                feeStrip: 0.0,
                accrualBasis: AccrualBasis.THIRTY_360,
                originalPrepaymentString: "O(120)"
            );
            deal.AddLoanToDeal(loan);

            CashFlowEngine engine = new CashFlowEngine();
            CashFlows cashflows = engine.RunCashFlows(deal, scenario);
            cashflows.PrettyPrint();
        }
    }
}
