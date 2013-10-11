using System;
using System.Linq;
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

        public int NativeWindowHandle
        {
            get { return _element.Current.NativeWindowHandle; }
        }

        public Element[] Children
        {
            get
            {
                return _element.FindAll(TreeScope.Children, Condition.TrueCondition).Cast<AutomationElement>()
                               .Select(x => new Element(x))
                               .ToArray();
            }
        }

        public Element[] ChildrenOf(AutomationProperty.Id id)
        {
            return _element.FindAll(TreeScope.Children, AutomationProperty.From(id)).Cast<AutomationElement>()
                           .Select(x => new Element(x))
                           .ToArray();
        }

        public void MouseClick()
        {
            Clicker.MouseClick(_element);
        }

        public static Element ById(string automationId)
        {
            var foundElement = AutomationElement.RootElement.FindFirst(TreeScope.Descendants, new PropertyCondition(AutomationElement.AutomationIdProperty, automationId));
            if (null == foundElement)
            {
                throw new ArgumentException(string.Format("An element with the id \"{0}\" was not found", automationId));
            }

            return new Element(foundElement);
        }

        public static Element ByHandle(IntPtr windowHandle)
        {
            var foundElement = AutomationElement.FromHandle(windowHandle);
            if (null == foundElement)
            {
                throw new ArgumentException(string.Format("An element with the handle 0x{0:x} was not found", windowHandle.ToInt32()));
            }

            return new Element(foundElement);
        }

        public static Element ByRuntimeId(int[] runtimeId)
        {
            var foundElement = AutomationElement.RootElement.FindFirst(TreeScope.Descendants, new PropertyCondition(AutomationElement.RuntimeIdProperty, runtimeId));
            if (null == foundElement)
            {
                throw new ArgumentException(string.Format("An element with the runtime id \"{0}\" was not found",
                                                          string.Join(", ", runtimeId.Select(x => x.ToString()))));
            }

            return new Element(foundElement);
        }
    }
}
