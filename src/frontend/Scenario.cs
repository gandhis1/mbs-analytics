using System;
using System.Runtime.InteropServices;

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