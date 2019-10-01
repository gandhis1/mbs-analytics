using System;
using System.Runtime.InteropServices;

namespace frontend
{
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
}