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
            get { return Find(TreeScope.Children, Condition.TrueCondition); }
        }

        public Element[] ChildrenOf(AutomationProperty.Id id)
        {
            return Find(TreeScope.Children, AutomationProperty.From(id));
        }

        public Element[] Descendants
        {
            get { return Find(TreeScope.Descendants, Condition.TrueCondition); }
        }

        public void MouseClick()
        {
            Clicker.MouseClick(_element);
        }

        public static Element ById(string automationId)
        {
            return FindFirst(new PropertyCondition(AutomationElement.AutomationIdProperty, automationId));
        }

        public static Element ByProcessId(int processId)
        {
            return FindFirst(new PropertyCondition(AutomationElement.ProcessIdProperty, processId));
        }

        public static Element ByHandle(IntPtr windowHandle)
        {
           return NullOr(AutomationElement.FromHandle(windowHandle));
        }

        public static Element ByRuntimeId(int[] runtimeId)
        {
            return FindFirst(new PropertyCondition(AutomationElement.RuntimeIdProperty, runtimeId));
        }

        private Element[] Find(TreeScope scope, Condition condition)
        {
            return _element.FindAll(scope, condition).Cast<AutomationElement>()
                           .Select(x => new Element(x))
                           .ToArray();
        }

        private static Element FindFirst(Condition condition)
        {
            return NullOr(AutomationElement.RootElement.FindFirst(TreeScope.Descendants, condition));
        }

        private static Element NullOr(AutomationElement automationElement)
        {
            return null == automationElement ? null : new Element(automationElement);
        }
    }
}
