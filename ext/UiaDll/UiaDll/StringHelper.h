#pragma once

using namespace System::Runtime::InteropServices;

ref class StringHelper
{
public:
  static void CopyToUnmanagedString(Exception^ e, char* destination, const int destinationSize)
  {
    CopyToUnmanagedString(e->Message + e->StackTrace, destination, destinationSize);
  }

  static void CopyToUnmanagedString(String^ source, char* destination, const int destinationSize)
  {
    auto unmanagedString = Marshal::StringToHGlobalAnsi(source);
    strncpy_s(destination, destinationSize, (const char*)(void*)unmanagedString,  _TRUNCATE);
    Marshal::FreeHGlobal(unmanagedString);
  }

  static char* ToUnmanaged(String^ source)
  {
    if( nullptr == source ) return NULL;

    const int numberOfBytes = source->Length + 1;
    auto unmanagedString = new char[numberOfBytes];
    CopyToUnmanagedString(source, unmanagedString, numberOfBytes);
    return unmanagedString;
  }
};

