using System;
using System.Collections.Generic;
using System.Linq;

using ExtensionMethods;

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
            Console.WriteLine(); // For spacing
            return (dealType, dealName, scenario);
        }

        public static string GetDealName()
        {
            Console.Write("\nEnter deal name:\n>> ");
            string dealName = Console.ReadLine();
            return dealName;
        }

        public static DealType ChooseDealType()
        {
            var selection = "";
            int selectionInt;
            while (!int.TryParse(selection, out selectionInt) || !Enumerable.Range(1, dealTypes.Length).Contains(selectionInt))
            {
                Console.WriteLine("\nSelect a deal type:");
                for (int i = 1; i <= dealTypes.Length; i++)
                {
                    Console.WriteLine(" {0}: {1}", i, dealTypes[i - 1].GetDisplayName());
                }
                Console.Write(">> ");
                selection = Console.ReadLine();
            }
            return dealTypes[selectionInt - 1];
        }

        public static Scenario ChooseScenario()
        {
            var selection = "";
            int selectionInt;
            while (!int.TryParse(selection, out selectionInt) || !Enumerable.Range(1, cannedScenarios.Count).Contains(selectionInt))
            {
                Console.WriteLine("\nSelect a scenario:");
                for (int i = 1; i <= cannedScenarios.Count; i++)
                {
                    Console.WriteLine(" {0}: {1}", i, cannedScenarios[i - 1].Key);
                }
                Console.Write(">> ");
                selection = Console.ReadLine();
            }
            return cannedScenarios[selectionInt - 1].Value;
        }

    }
}