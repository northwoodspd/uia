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

        public virtual bool IsEnabled
        {
            get { return _element.Current.IsEnabled; }
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

        public static Element From(AutomationElement element)
        {
            return new Element(element);
        }

        public static Element ById(string automationId)
        {
            return FindFirst(automationId.IdCondition());
        }

        public Element ChildById(string automationId)
        {
            return FindFirst(TreeScope.Descendants, automationId.IdCondition());
        }

        public static Element ByName(string name)
        {
            return FindFirst(new PropertyCondition(AutomationElement.NameProperty, name));
        }

        public Element ChildByName(string name)
        {
            return FindFirst(TreeScope.Descendants, new PropertyCondition(AutomationElement.NameProperty, name));
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
            return FindFirst(new PropertyCondition(AutomationElement.RuntimeIdProperty, runtimeId), TreeScope.Descendants);
        }

        private Element[] Find(TreeScope scope, Condition condition)
        {
            return _element.FindAll(scope, condition).Cast<AutomationElement>()
                           .Select(x => new Element(x))
                           .ToArray();
        }

        private Element FindFirst(TreeScope scope, Condition condition)
        {
            return NullOr(_element.FindFirst(scope, condition));
        }

        private static Element FindFirst(Condition condition, TreeScope scope = TreeScope.Children)
        {
            return NullOr(AutomationElement.RootElement.FindFirst(scope, condition));
        }

        private static Element NullOr(AutomationElement automationElement)
        {
            return null == automationElement ? null : new Element(automationElement);
        }
    }
}
