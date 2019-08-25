using System;
using System.Runtime.InteropServices;

namespace frontend
{
    class Program

    {
        static void Main(string[] args)
        {
            Scenario scenario = new Scenario(0.05, 0.01, 0.25, 0, 0.0, 100.0, 100.0);
            CashFlowEngine engine = new CashFlowEngine();
            Loan loan = new Loan(); // TODO: Update all interfaces to accept parameters
            CashFlows cashflows = engine.RunCashFlows(loan, scenario);
            scenario.PrettyPrint();
            cashflows.PrettyPrint();
        }

    }

    interface IPrettyPrintable
    {
        void PrettyPrint();
    }

    public sealed class CashFlowEngine : IDisposable
    {
        [DllImport("../../bin/mbs_analytics.dll")]
        private static extern IntPtr CreateEngine();
        [DllImport("../../bin/mbs_analytics.dll")]
        public static extern void DeleteEngine(IntPtr engine);
        [DllImport("../../bin/mbs_analytics.dll")]
        private static extern IntPtr RunCashFlows(IntPtr engine, IntPtr loan, IntPtr scenario);

        private IntPtr engine;

        public CashFlowEngine()
        {
            engine = CreateEngine();
        }

        public CashFlows RunCashFlows(Loan loan, Scenario scenario)
        {
            return new CashFlows(RunCashFlows(engine, loan, scenario));
        }

        public void Dispose()
        {
            if (engine != IntPtr.Zero)
            {
                DeleteEngine(engine);
            }
            GC.SuppressFinalize(this);
        }

        ~CashFlowEngine()
        {
            Dispose();
        }
    }

    public sealed class Scenario : IDisposable, IPrettyPrintable
    {
        [DllImport("../../bin/mbs_analytics")]
        private static extern IntPtr CreateScenario(double vpr, double cdr, double sev, int lag, double dq, double prinAdv, double intAdv);
        [DllImport("../../bin/mbs_analytics.dll")]
        public static extern void DeleteScenario(IntPtr scenario);
        [DllImport("../../bin/mbs_analytics.dll")]
        public static extern IntPtr PrettyDescriptionScenario(IntPtr scenario);
        private IntPtr scenario;

        public Scenario(double vpr, double cdr, double sev, int lag, double dq, double prinAdv, double intAdv)
        {
            scenario = CreateScenario(vpr, cdr, sev, lag, dq, prinAdv, intAdv);
        }

        public static implicit operator IntPtr(Scenario scenario) => scenario.scenario;

        public void PrettyPrint()
        {
            Console.WriteLine(Marshal.PtrToStringAnsi(PrettyDescriptionScenario(scenario)));
        }

        public void Dispose()
        {
            if (scenario != IntPtr.Zero)
            {
                DeleteScenario(scenario);
            }
            GC.SuppressFinalize(this);
        }

        ~Scenario()
        {
            Dispose();
        }
    }

    public sealed class Loan
    {
        [DllImport("../../bin/mbs_analytics")]
        public static extern IntPtr CreateLoan();  // TODO: Add parameters and stop using a canned loan
        [DllImport("../../bin/mbs_analytics.dll")]
        public static extern void DeleteLoan(IntPtr loan);
        private IntPtr loan;

        public Loan()  // TODO: Add parameters and stop using a canned loan
        {
            loan = CreateLoan();  // TODO: Add parameters and stop using a canned loan
        }

        public static implicit operator IntPtr(Loan loan) => loan.loan;

        public void Dispose()
        {
            if (loan != IntPtr.Zero)
            {
                DeleteLoan(loan);
            }
            GC.SuppressFinalize(this);
        }

        ~Loan()
        {
            Dispose();
        }
    }

    public sealed class CashFlows : IDisposable, IPrettyPrintable
    {
        [DllImport("../../bin/mbs_analytics.dll")]
        public static extern void DeleteCashFlows(IntPtr cashflows);
        [DllImport("../../bin/mbs_analytics.dll")]
        public static extern IntPtr PrettyDescriptionCashFlows(IntPtr cashflows);
        private IntPtr cashflows;

        public CashFlows(IntPtr cashflows)
        {
            this.cashflows = cashflows;
        }

        public void PrettyPrint()
        {
            Console.WriteLine(Marshal.PtrToStringAnsi(PrettyDescriptionCashFlows(cashflows)));
        }

        public void Dispose()
        {
            if (cashflows != IntPtr.Zero)
            {
                DeleteCashFlows(cashflows);
            }
            GC.SuppressFinalize(this);
        }

        ~CashFlows()
        {
            Dispose();
        }
    }
}
