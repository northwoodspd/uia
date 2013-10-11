#pragma once

using namespace System::Runtime::InteropServices;

ref class StringHelper
{
public:
  static void CopyToUnmanagedString(String^ source, char* destination, const int destinationSize);
  static char* ToUnmanaged(String^ string);
};

