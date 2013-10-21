#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Invoke(PElementInformation element, char* errorInfo, const int errorInfoLength) {
    try {
      Find(element)->As<InvokePattern^>(InvokePattern::Pattern)->Invoke();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }
}