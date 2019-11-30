using System;
using System.Runtime.InteropServices;

namespace frontend
{
    public enum AccrualBasis
    {
        THIRTY_360,
        ACTUAL_360
    }

    public sealed class Loan : IPrettyPrintable
    {
        [DllImport("../../bin/mbs_analytics", CharSet = CharSet.Ansi)]
        private static extern IntPtr CreateLoan([MarshalAs(UnmanagedType.LPStr)] string loanId, double originalBalance, double currentBalance, int firstPaymentDateYYYYMMDD, int factorDateYYYYMMDD, int originalLoanTerm, int originalAmortTerm, int originalIOTerm, double grossCoupon, double feeStrip, AccrualBasis accrualBasis, string originalPrepaymentString);
        [DllImport("../../bin/mbs_analytics")]
        private static extern void DeleteLoan(IntPtr loan);
        [DllImport("../../bin/mbs_analytics")]
        private static extern IntPtr PrettyDescriptionLoan(IntPtr loan);
        private IntPtr loan;
        public static implicit operator IntPtr(Loan loan) => loan.loan;

        public Loan(string loanId, double originalBalance, double currentBalance, DateTime firstPaymentDate, DateTime factorDate, int originalLoanTerm, int originalAmortTerm, int originalIOTerm, double grossCoupon, double feeStrip, AccrualBasis accrualBasis, string originalPrepaymentString)
        {
            loan = CreateLoan(loanId, originalBalance, currentBalance, firstPaymentDate.toYYYYMMDD(), factorDate.toYYYYMMDD(), originalLoanTerm, originalAmortTerm, originalIOTerm, grossCoupon, feeStrip, accrualBasis, originalPrepaymentString);
        }


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
}