using System;
using System.Windows.Automation;

namespace UIA.Helper
{
    public class Element
    {
        private readonly AutomationElement _element;

        private Element(AutomationElement element)
        {
            _element = element;
        }

        public int[] RuntimeId
        {
            get { return _element.GetRuntimeId(); }
        }

        public string Name
        {
            get { return _element.Current.Name; }
        }

        public static Element ById(string automationId)
        {
            var foundElement = AutomationElement.RootElement.FindFirst(TreeScope.Children, new PropertyCondition(AutomationElement.AutomationIdProperty, automationId));
            if (null == foundElement)
            {
                throw new ArgumentException(string.Format("An element with the id \"{0}\" was not found", automationId));
            }

            return new Element(foundElement);
        }
    }
}
