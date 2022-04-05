using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace frontend
{
    public enum VPRType
    {
        SMM,
        CPR,
        CPY,
        CPP,
        CPJ,
        CPB,
        PSA
    }

    public enum CDRType
    {
        MDR,
        CDR,
        PLD
    }

    public sealed class Scenario : IDisposable, IPrettyPrintable
    {
        [DllImport("mbs_analytics")]
        private static extern IntPtr CreateScenario(double vpr, double cdr, double sev, int lag, double dq, double prinAdv, double intAdv, VPRType vprType, CDRType cdrType);
        [DllImport("mbs_analytics")]
        private static extern IntPtr CreateVectorScenario([In, Out] double[] vpr, [In, Out] double[] cdr, [In, Out] double[] sev, [In, Out] int[] lag, [In, Out] double[] dq, [In, Out] double[] prinAdv, [In, Out] double[] intAdv, VPRType vprType, CDRType cdrType, int vectorSize);
        [DllImport("mbs_analytics")]
        private static extern void DeleteScenario(IntPtr scenario);
        [DllImport("mbs_analytics")]
        private static extern IntPtr PrettyDescriptionScenario(IntPtr scenario);
        private IntPtr scenario;

        public Scenario(double vpr, double cdr, double sev, int lag, double dq, double prinAdv, double intAdv, VPRType vprType = VPRType.CPR, CDRType cdrType = CDRType.CDR)
        {
            scenario = CreateScenario(vpr, cdr, sev, lag, dq, prinAdv, intAdv, vprType, cdrType);
        }

        public Scenario(IEnumerable<double> vpr, IEnumerable<double> cdr, IEnumerable<double> sev, IEnumerable<int> lag, IEnumerable<double> dq, IEnumerable<double> prinAdv, IEnumerable<double> intAdv, VPRType vprType = VPRType.CPR, CDRType cdrType = CDRType.CDR)
        {
            scenario = CreateVectorScenario(vpr.ToArray(), cdr.ToArray(), sev.ToArray(), lag.ToArray(), dq.ToArray(), prinAdv.ToArray(), intAdv.ToArray(), vprType, cdrType, vpr.Count());
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
}