#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Invoke(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      ElementFrom(element)->As<InvokePattern^>(InvokePattern::Pattern)->Invoke();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }
}