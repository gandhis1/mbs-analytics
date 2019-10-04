using System;
using System.ComponentModel.DataAnnotations;
using System.Reflection;
using System.Diagnostics;

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
    }
}
