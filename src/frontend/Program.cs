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
            Loan loan = new Loan("1717469130", 763000.0, 763000.0, new DateTime(2019, 2, 1), 60, 360, 0, 28, 0.0496, 0.0248, AccrualBasis.ACTUAL_360, "YM (54) O(6)");
            CashFlows cashflows = engine.RunCashFlows(loan, scenario);
            scenario.PrettyPrint();
            loan.PrettyPrint();
            //cashflows.PrettyPrint();
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

    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct StructDateTime
    {
        int tm_sec;
        int tm_min;
        int tm_hour;
        int tm_mday;
        int tm_mon;
        int tm_year;
        int tm_wday;
        int tm_yday;
        int tm_isdst;
        public static implicit operator StructDateTime(DateTime dt)
        {
            return new DateTime(2019, 2, 1);  // TODO: Implement a real conversion instead of this hard-code
        }
    }

    public enum AccrualBasis
    {
        THIRTY_360,
        ACTUAL_360
    }

    public sealed class Loan : IPrettyPrintable
    {
        [DllImport("../../bin/mbs_analytics", CharSet = CharSet.Ansi)]
        public static extern IntPtr CreateLoan([MarshalAs(UnmanagedType.LPStr)] string loanId, double originalBalance, double currentBalance); //, StructDateTime factorDate, int originalLoanTerm, int originalAmortTerm, int originalIOTerm, int currentLoanAge, double grossCoupon, double feeStrip, AccrualBasis accrualBasis, string originalPrepaymentString);
        [DllImport("../../bin/mbs_analytics.dll")]
        public static extern void DeleteLoan(IntPtr loan);
        [DllImport("../../bin/mbs_analytics.dll")]
        public static extern IntPtr PrettyDescriptionLoan(IntPtr loan);
        private IntPtr loan;

        public Loan(string loanId, double originalBalance, double currentBalance, DateTime factorDate, int originalLoanTerm, int originalAmortTerm, int originalIOTerm, int currentLoanAge, double grossCoupon, double feeStrip, AccrualBasis accrualBasis, string originalPrepaymentString)
        {
            loan = CreateLoan(loanId, originalBalance, currentBalance);//, factorDate, originalLoanTerm, originalAmortTerm, originalIOTerm, currentLoanAge, grossCoupon, feeStrip, accrualBasis, originalPrepaymentString);
        }

        public static implicit operator IntPtr(Loan loan) => loan.loan;

        public void PrettyPrint()
        {
            Console.WriteLine(Marshal.PtrToStringAnsi(PrettyDescriptionLoan(loan)));
        }

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
