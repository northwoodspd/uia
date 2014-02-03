using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Windows;
using System.Windows.Automation;

namespace UIA.Helper
{
    public static class Extensions
    {
        public static string Join<T>(this IEnumerable<T> items, string separator = ", ")
        {
            return string.Join(separator, items.Select(x => x.ToString()));
        }
    }

    public static class PropertyExtensions
    {
        public static Condition IdCondition(this string automationId)
        {
            return new PropertyCondition(AutomationElement.AutomationIdProperty, automationId);
        }

        public static Condition NameCondition(this string name)
        {
            return new PropertyCondition(AutomationElement.NameProperty, name);
        }
    }

    public static class ElementExtensions
    {
        public static bool TryToFocus(this AutomationElement automationElement)
        {
            try
            {
                var timesTried = 0;
                while (timesTried++ < 5 && !automationElement.Current.HasKeyboardFocus)
                {
                    automationElement.SetFocus();
                    Thread.Sleep(100);
                }
                return automationElement.Current.HasKeyboardFocus;
            } catch { return false; }
        }

        public static bool ScrollToIfPossible(this AutomationElement automationElement)
        {
            if (!automationElement.CanScrollTo())
            {
                return false;
            }

            if (!automationElement.HasClickablePoint())
            {
                automationElement.AsScrollItem().ScrollIntoView();
                automationElement.WaitUntilClickable(3);
            }

            return true;
        }


        public static bool CanScrollTo(this AutomationElement automationElement)
        {
            return (bool)automationElement.GetCurrentPropertyValue(AutomationElement.IsScrollItemPatternAvailableProperty);
        }


        public static bool HasClickablePoint(this AutomationElement automationElement)
        {
            Point point;
            return automationElement.TryGetClickablePoint(out point);
        }


        public static void WaitUntilClickable(this AutomationElement automationElement, int howManySeconds)
        {
            var then = DateTime.Now;
            while (!automationElement.HasClickablePoint())
            {
                Thread.Sleep(1);
                if ((DateTime.Now - then).Seconds > howManySeconds)
                {
                    throw new Exception(string.Format("Waited for more than {0} seconds to be able to click this", howManySeconds));
                }
            }
        }

        public static ScrollItemPattern AsScrollItem(this AutomationElement automationElement)
        {
            return automationElement.As<ScrollItemPattern>(ScrollItemPatternIdentifiers.Pattern);
        }

        public static T As<T>(this AutomationElement automationElement, AutomationPattern pattern)
        {
            return (T)automationElement.GetCurrentPattern(pattern);
        }
    }
}
