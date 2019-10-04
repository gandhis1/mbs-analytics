using System;

namespace frontend
{
    class Program

    {
        static void Main(string[] args)
        {
            var (dealType, dealName, scenario) = CommandLineInterface.GetUserInputs();
            CashFlowEngine engine = new CashFlowEngine();
            Deal deal = new Deal("FN AN3073");
            for (int i = 1; i < 200_000; i++)
            {
                Loan loan = new Loan(
                    loanId: "1717469130",
                    originalBalance: 763000.0,
                    currentBalance: 763000.0,
                    factorDate: new DateTime(2019, 2, 1),
                    originalLoanTerm: 60,
                    originalAmortTerm: 360,
                    originalIOTerm: 0,
                    currentLoanAge: 0,
                    grossCoupon: 0.0496 / i,
                    feeStrip: 0.0248 / i,
                    accrualBasis: AccrualBasis.ACTUAL_360,
                    originalPrepaymentString: "YM(54) O(6)"
                );
                deal.AddLoanToDeal(loan);
            }
            CashFlows cashflows = engine.RunCashFlows(deal, scenario);
            cashflows.PrettyPrint();
        }
    }
}
