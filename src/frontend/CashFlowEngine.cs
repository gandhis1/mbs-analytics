using System;
using System.Runtime.InteropServices;

namespace frontend
{
    public sealed class CashFlowEngine : IDisposable
    {
        [DllImport("mbs_analytics")]
        private static extern IntPtr CreateEngine();
        [DllImport("mbs_analytics")]
        private static extern void DeleteEngine(IntPtr engine);
        [DllImport("mbs_analytics")]
        private static extern IntPtr RunCashFlows(IntPtr engine, IntPtr deal, IntPtr scenario);

        private IntPtr engine;

        public CashFlowEngine()
        {
            engine = CreateEngine();
        }

        public CashFlows RunCashFlows(Deal deal, Scenario scenario)
        {
            return new CashFlows(RunCashFlows(engine, deal, scenario));
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