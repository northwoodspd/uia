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

        public static Element From(AutomationElement element)
        {
            return null == element ? null : new Element(element);
        }

        public static Element[] From(AutomationElement[] elements)
        {
            return elements.Select(x => new Element(x)).ToArray();
        }

        public TPattern As<TPattern>(AutomationPattern pattern)
        {
            return (TPattern)_element.GetCurrentPattern(pattern);
        }

        public void SendKeys(string keysToSend)
        {
            _element.TryToFocus();
            System.Windows.Forms.SendKeys.SendWait(keysToSend);
        }

        public void SetFocus()
        {
            _element.SetFocus();
        }

        public virtual int[] RuntimeId
        {
            get { return _element.GetRuntimeId(); }
        }

        public virtual long[] BoundingRectangle
        {
            get
            {
                var r = _element.Current.BoundingRectangle;
                return new[] { (long)r.Left, (long)r.Top, (long)(r.Right - r.Left), (long)(r.Bottom - r.Top) };
            }
        }

        public virtual string Name
        {
            get { return _element.Current.Name; }
        }

        public virtual string ClassName
        {
            get { return _element.Current.ClassName; }
        }

        public virtual string Id
        {
            get { return _element.Current.AutomationId; }
        }

        public virtual bool IsEnabled
        {
            get { return _element.Current.IsEnabled; }
        }

        public virtual bool IsVisible
        {
            get { return _element.Current.IsOffscreen == false; }
        }

        public virtual bool HasKeyboardFocus
        {
            get { return _element.Current.HasKeyboardFocus; }
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

        public static Element[] Windows
        {
            get { return Find(AutomationElement.RootElement, TreeScope.Children, Condition.TrueCondition); }
        }

        public Element[] Children
        {
            get { return Find(TreeScope.Children, Condition.TrueCondition); }
        }

        public Element[] Descendants
        {
            get { return Find(TreeScope.Descendants, Condition.TrueCondition); }
        }

        public void ClickClickablePoint()
        {
            Mouse.ClickClickablePoint(_element);
        }

        public void ClickCenter()
        {
            Mouse.ClickCenter(_element);
        }

        public Element[] Find(TreeScope scope, Condition condition)
        {
            return Find(_element, scope, condition);
        }

        public Element FindFirst(TreeScope scope, Condition condition)
        {
            return NullOr(_element.FindFirst(scope, condition));
        }

        public static Element ById(string automationId)
        {
            return FindFirst(automationId.IdCondition());
        }

        public Element ChildById(string automationId, TreeScope scope)
        {
            return FindFirst(scope, automationId.IdCondition());
        }

        public static Element ByName(string name)
        {
            return FindFirst(new PropertyCondition(AutomationElement.NameProperty, name));
        }

        public Element ChildByName(string name, TreeScope scope)
        {
            return FindFirst(scope, new PropertyCondition(AutomationElement.NameProperty, name));
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

        private static Element[] Find(AutomationElement element, TreeScope scope, Condition condition)
        {
            return element.FindAll(scope, condition).Cast<AutomationElement>()
                           .Select(x => new Element(x))
                           .ToArray();
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
