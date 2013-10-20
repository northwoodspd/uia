#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Value_Release(PValuePatternInformation valueInformation) {
    delete valueInformation;
  }

  __declspec(dllexport) void Value_Set(PElementInformation element, const char* value, char* errorInfo, const int errorInfoLength) {
    try {
      Find(element)->As<ValuePattern^>(ValuePattern::Pattern)->SetValue(gcnew String(value));
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }

  __declspec(dllexport) PValuePatternInformation Value_Information(PElementInformation element, char* errorInfo, const int errorInfoLength) {
    try {
      auto valuePattern = Find(element)->As<ValuePattern^>(ValuePattern::Pattern);
      return new ValuePatternInformation(valuePattern->Current);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return NULL;
    }
  }
}