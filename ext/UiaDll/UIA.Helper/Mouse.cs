using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Forms;

namespace UIA.Helper
{
    public class Mouse
    {
        [DllImport("user32.dll")]
        static extern void mouse_event(uint flags, uint x, uint y, uint data, int extraInfo);

        private const uint MOUSEEVENTLF_MOVE = 0x1;
        private const uint MOUSEEVENTLF_LEFTDOWN = 0x2;
        private const uint MOUSEEVENTLF_LEFTUP = 0x4;

        public static void Drag(int startX, int startY, int endX, int endY)
        {
            Cursor.Position = new System.Drawing.Point(startX, startY);
            Down();

            Move((uint)((startX + endX) / 2), (uint)((startY + endY) / 2));

            Cursor.Position = new System.Drawing.Point(endX, endY);
            Up();
        }

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

            Cursor.Position = new System.Drawing.Point((int)point.X, (int)point.Y);
            Down();
            Up();
        }

        private static void Up()
        {
            mouse_event(MOUSEEVENTLF_LEFTUP, 0, 0, 0, 0);
        }

        private static void Down()
        {
            mouse_event(MOUSEEVENTLF_LEFTDOWN, 0, 0, 0, 0);
        }

        private static void Move(uint x, uint y)
        {
            mouse_event(MOUSEEVENTLF_MOVE, x, y, 0, 0);
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