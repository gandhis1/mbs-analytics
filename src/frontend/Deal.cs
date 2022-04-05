using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace frontend
{
    public sealed class Deal : IDisposable
    {
        [DllImport("mbs_analytics")]
        private static extern IntPtr CreateDeal(string name);
        [DllImport("mbs_analytics")]
        private static extern void AddLoanToDeal(IntPtr deal, IntPtr loan, string group);
        [DllImport("mbs_analytics")]
        private static extern void DeleteDeal(IntPtr deal);

        private IntPtr deal;

        public static implicit operator IntPtr(Deal deal) => deal.deal;

        public Deal(string name)
        {
            deal = CreateDeal(name);
        }

        public void AddLoanToDeal(Loan loan, string group = "all")
        {
            AddLoanToDeal(deal, loan, group);
        }

        public void AddLoansToDeal(IEnumerable<Loan> loans, string group = "all")
        {
            foreach (Loan loan in loans)
            {
                AddLoanToDeal(loan, group);
            }
        }

        public void Dispose()
        {
            if (deal != IntPtr.Zero)
            {
                DeleteDeal(deal);
            }
            GC.SuppressFinalize(this);
        }

        ~Deal()
        {
            Dispose();
        }
    }
}