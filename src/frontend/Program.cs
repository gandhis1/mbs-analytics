using System;

namespace frontend
{
    class Program

    {
        static void Main(string[] args)
        {
            var (dealType, dealName, scenario) = CommandLineInterface.GetUserInputs();
            CashFlowEngine engine = new CashFlowEngine();
            Loan loan = new Loan(
                loanId: "1717469130",
                originalBalance: 763000.0,
                currentBalance: 763000.0,
                factorDate: new DateTime(2019, 2, 1),
                originalLoanTerm: 60,
                originalAmortTerm: 360,
                originalIOTerm: 0,
                currentLoanAge: 0,
                grossCoupon: 0.0496,
                feeStrip: 0.0248,
                accrualBasis: AccrualBasis.ACTUAL_360,
                originalPrepaymentString: "L(12) YM(36) 1%(6) O(6)"
            );
            CashFlows cashflows = engine.RunCashFlows(loan, scenario);
            scenario.PrettyPrint();
            loan.PrettyPrint();
            cashflows.PrettyPrint();
        }
    }
}
