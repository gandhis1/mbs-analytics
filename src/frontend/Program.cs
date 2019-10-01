using System;

namespace frontend
{
    class Program

    {
        static void Main(string[] args)
        {
            Scenario scenario = new Scenario(0.05, 0.01, 0.25, 0, 0.0, 100.0, 100.0);
            CashFlowEngine engine = new CashFlowEngine();
            Loan loan = new Loan("1717469130", 763000.0, 763000.0, new DateTime(2019, 2, 1), 60, 360, 0, 28, 0.0496, 0.0248, AccrualBasis.ACTUAL_360, "YM(54) O(6)");
            CashFlows cashflows = engine.RunCashFlows(loan, scenario);
            scenario.PrettyPrint();
            loan.PrettyPrint();
            //cashflows.PrettyPrint();
        }
    }
}
