using System;
using System.Runtime.InteropServices;

namespace UIA.Helper
{
    class Win32
    {
        [DllImport("user32")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool IsWindow(IntPtr hWnd);
    }
}