using System.Collections.Generic;
using System.Linq;

namespace UIA.Helper
{
    public static class Extensions
    {
        public static string Join<T>(this IEnumerable<T> items, string separator = ", ")
        {
            return string.Join(separator, items.Select(x => x.ToString()));
        }
    }
}
