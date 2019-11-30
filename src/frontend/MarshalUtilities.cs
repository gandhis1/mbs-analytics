using System;

namespace frontend
{
    public static class ExtensionMethods
    {
        public static int toYYYYMMDD(this DateTime dateTime)
        {
            return int.Parse(dateTime.ToString("yyyyMMdd"));
        }
    }
}