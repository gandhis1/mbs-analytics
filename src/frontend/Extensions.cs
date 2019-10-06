using System;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Reflection;
using System.Runtime.Serialization.Formatters.Binary;

namespace ExtensionMethods
{
    public static class ExtensionMethods
    {
        public static string GetDisplayName(this Enum value)
        {
            Debugger.Launch();
            Type type = value.GetType();
            string name = Enum.GetName(type, value);
            FieldInfo field = type.GetField(name);
            var attr = (DisplayAttribute) Attribute.GetCustomAttribute(field, typeof(DisplayAttribute));
            return attr.Name;
        }

        public static void SaveToFile(this CookieContainer cookies, String path)
        {
            var formatter = new BinaryFormatter();
            using (var fileStream = File.OpenWrite(path))
            {
                formatter.Serialize(fileStream, cookies);
            }
        }

        public static void LoadFromFile(this CookieContainer cookies, String path)
        {
            var formatter = new BinaryFormatter();
            using (var fileStream = File.OpenRead(path))
            {
                cookies = (CookieContainer)formatter.Deserialize(fileStream);
            }
        }
    }
}
