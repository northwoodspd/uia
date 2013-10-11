using System;
using System.Windows.Automation;

namespace UIA.Helper
{
    public class AutomationProperty
    {
        public enum Id
        {
            IsSelectionItem = 0,
        }

        public static PropertyCondition From(Id id)
        {
            switch (id)
            {
                case Id.IsSelectionItem:
                    return new PropertyCondition(AutomationElement.IsSelectionItemPatternAvailableProperty, true);
                default:
                    throw new ArgumentException(id + " is not a supported property");
            }
        }
    }
}
