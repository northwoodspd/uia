#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Toggle(PElementInformation element, char* errorInfo, const int errorInfoLength) {
    try {
      Find(element)->As<TogglePattern^>(TogglePattern::Pattern)->Toggle();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }
}