using System;
using System.Linq;
using System.Windows.Automation;

namespace UIA.Helper
{
    public class Element
    {
        private readonly AutomationElement _element;

        protected Element()
        {
        }

        private Element(AutomationElement element)
        {
            _element = element;
        }

        public TPattern As<TPattern>(AutomationPattern pattern)
        {
            return (TPattern) _element.GetCurrentPattern(pattern);
        }

        public virtual int[] RuntimeId
        {
            get { return _element.GetRuntimeId(); }
        }

        public virtual string Name
        {
            get { return _element.Current.Name; }
        }

        public virtual string Id
        {
            get { return _element.Current.AutomationId; }
        }

        public virtual int NativeWindowHandle
        {
            get { return _element.Current.NativeWindowHandle; }
        }

        public virtual int ControlTypeId
        {
            get { return _element.Current.ControlType.Id; }
        }

        public virtual int[] SupportedPatternIds
        {
            get { return _element.GetSupportedPatterns().Select(x => x.Id).ToArray(); }
        }

        public Element[] Children
        {
            get { return Find(TreeScope.Children, Condition.TrueCondition); }
        }

        public Element[] ChildrenOf(AutomationPropertyCondition.Id id)
        {
            return Find(TreeScope.Children, AutomationPropertyCondition.From(id));
        }

        public Element[] Descendants
        {
            get { return Find(TreeScope.Descendants, Condition.TrueCondition); }
        }

        public void MouseClick()
        {
            Clicker.MouseClick(_element);
        }

        public static Element Root()
        {
            return new Element(AutomationElement.RootElement);
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
