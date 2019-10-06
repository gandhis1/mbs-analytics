using System;

namespace frontend
{
    class Program

    {
        static void Main(string[] args)
        {
            var (dealName, dealType, scenario) = CommandLineInterface.GetUserInputs();
            Deal deal = Data.GetDataLoader(dealType).LoadDeal(dealName);
            CashFlowEngine engine = new CashFlowEngine();
            CashFlows cashflows = engine.RunCashFlows(deal, scenario);
            cashflows.PrettyPrint();
        }
    }
}
