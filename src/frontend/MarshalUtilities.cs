using System;
using System.Runtime.InteropServices;

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
        return new StructDateTime
        {
            tm_sec = dt.Second,
            tm_min = dt.Minute,
            tm_hour = dt.Hour,
            tm_mday = dt.Day,
            tm_mon = dt.Month - 1,
            tm_year = dt.Year - 1900,
            tm_wday = (int)dt.DayOfWeek,
            tm_yday = dt.DayOfYear,
            tm_isdst = Convert.ToInt32(dt.IsDaylightSavingTime())
        };
    }
}