#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Value_Release(ValuePatternInformationPtr valueInformation) {
    delete valueInformation;
  }

  __declspec(dllexport) void Value_Set(ElementInformationPtr element, const char* value, char* errorInfo, const int errorInfoLength) {
    try {
      ElementFrom(element)->As<ValuePattern^>(ValuePattern::Pattern)->SetValue(gcnew String(value));
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }

  __declspec(dllexport) ValuePatternInformationPtr Value_Information(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      auto valuePattern = ElementFrom(element)->As<ValuePattern^>(ValuePattern::Pattern);
      return new ValuePatternInformation(valuePattern->Current);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return NULL;
    }
  }
}