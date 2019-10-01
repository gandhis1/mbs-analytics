using System;
using System.Runtime.InteropServices;

namespace frontend
{
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