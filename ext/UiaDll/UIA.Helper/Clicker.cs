using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Forms;

namespace UIA.Helper
{
    public class Clicker
    {
        [DllImport("user32.dll")]
        static extern void mouse_event(uint flags, uint x, uint y, uint data, int extraInfo);

        [Flags]
        public enum MouseEvent
        {
            Leftdown = 0x00000002,
            Leftup = 0x00000004,
        }

        private const uint MOUSEEVENTLF_LEFTDOWN = 0x2;
        private const uint MOUSEEVENTLF_LEFTUP = 0x4;

        public static void ClickClickablePoint(AutomationElement element)
        {
            Click(element, element.GetClickablePoint);
        }

        public static void ClickCenter(AutomationElement element)
        {
            Click(element, () => Center(element));
        }

        private static void Click(AutomationElement element, Func<Point> GetPoint)
        {
            element.ScrollToIfPossible();
            element.TryToFocus();

            var point = GetPoint();

            Cursor.Position = new System.Drawing.Point((int) point.X, (int) point.Y);
            mouse_event(MOUSEEVENTLF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTLF_LEFTUP, 0, 0, 0, 0);
        }

        private static Point Center(AutomationElement element)
        {
            try
            {
                return element.GetClickablePoint();
            }
            catch (Exception)
            {
                return element.Current.BoundingRectangle.Center();
            }
        }
    }
}