using System;
using System.Collections.Generic;
using System.Linq;

namespace frontend
{
    static class CommandLineInterface
    {
        private static DealType[] dealTypes = Enum.GetValues(typeof(DealType)).Cast<DealType>().ToArray();
        private static List<KeyValuePair<String, Scenario>> cannedScenarios = new List<KeyValuePair<String, Scenario>>{
            KeyValuePair.Create("0 CPR", new Scenario(vpr: 0.0, cdr: 0.0, sev: 0.0, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0)),
            KeyValuePair.Create("5 CPR", new Scenario(vpr: 0.05, cdr: 0.0, sev: 0.0, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0)),
            KeyValuePair.Create("10 CPR", new Scenario(vpr: 0.10, cdr: 0.0, sev: 0.0, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0)),
            KeyValuePair.Create("15 CPR", new Scenario(vpr: 0.15, cdr: 0.0, sev: 0.0, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0)),
            KeyValuePair.Create("15 CPB", new Scenario(vpr: 0.15, cdr: 0.0, sev: 0.0, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0, VPRType.CPB)),
            KeyValuePair.Create("15 CPJ", new Scenario(vpr: 0.15, cdr: 0.0, sev: 0.0, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0, VPRType.CPJ, CDRType.PLD)),
            KeyValuePair.Create("100 CPR", new Scenario(vpr: 1.0, cdr: 0.0, sev: 0.0, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0)),
            KeyValuePair.Create("100 CPY", new Scenario(vpr: 1.0, cdr: 0.0, sev: 0.0, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0, VPRType.CPY)),
            KeyValuePair.Create("100 CPP", new Scenario(vpr: 1.0, cdr: 0.0, sev: 0.0, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0, VPRType.CPP)),
            KeyValuePair.Create("5 CDR | 75 SEV", new Scenario(vpr: 0.0, cdr: 0.05, sev: 0.75, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0)),
            KeyValuePair.Create("50 CDR | 100 SEV", new Scenario(vpr: 0.0, cdr: 0.50, sev: 1.0, lag: 0, dq: 0.0, prinAdv: 1.0, intAdv: 1.0)),
            KeyValuePair.Create("5 CPR | 1 DQ | 2 CDR | 50 SEV | 6 LAG", new Scenario(vpr: 0.05, cdr: 0.02, sev: 0.50, lag: 6, dq: 0.01, prinAdv: 1.0, intAdv: 1.0))
        };

        public static (DealType, string, Scenario) GetUserInputs()
        {
            var dealType = ChooseDealType();
            var dealName = GetDealName();
            var scenario = ChooseScenario();
            return (dealType, dealName, scenario);
        }

        public static string GetDealName()
        {
            Console.Write("\nEnter deal name: ");
            string dealName = Console.ReadLine();
            return dealName;
        }

        public static DealType ChooseDealType()
        {
            var selection = "";
            int enumIndex;
            while (!int.TryParse(selection, out enumIndex) || !Enumerable.Range(1, dealTypes.Length).Contains(enumIndex))
            {
                Console.WriteLine("\nSelect a deal type:");
                for (int i = 1; i <= dealTypes.Length; i++)
                {
                    Console.WriteLine("  " + i + ": " + dealTypes[i - 1]);
                }
                Console.WriteLine();
                selection = Console.ReadLine();
            }
            return dealTypes[enumIndex - 1];
        }

        public static Scenario ChooseScenario()
        {
            var selection = "";
            int enumIndex;
            while (!int.TryParse(selection, out enumIndex) || !Enumerable.Range(1, cannedScenarios.Count).Contains(enumIndex))
            {
                Console.WriteLine("\n Select a scenario:");
                for (int i = 1; i <= cannedScenarios.Count; i++)
                {
                    Console.WriteLine("  " + i + ": " + cannedScenarios[i - 1].Key);
                }
                Console.WriteLine();
                selection = Console.ReadLine();
            }
            return cannedScenarios[enumIndex - 1].Value;
        }

    }
}