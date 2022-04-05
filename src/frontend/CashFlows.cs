using System;
using System.Runtime.InteropServices;

namespace frontend
{
    public sealed class CashFlows : IDisposable, IPrettyPrintable
    {
        [DllImport("mbs_analytics")]
        private static extern void DeleteCashFlows(IntPtr cashflows);
        [DllImport("mbs_analytics")]
        private static extern IntPtr PrettyDescriptionCashFlows(IntPtr cashflows, bool detailed);
        private IntPtr cashflows;

        public CashFlows(IntPtr cashflows)
        {
            this.cashflows = cashflows;
        }

        public void PrettyPrint()
        {
            Console.WriteLine(Marshal.PtrToStringAnsi(PrettyDescriptionCashFlows(cashflows, true)));
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