#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Toggle_Release(ToggleInformationPtr toggleInfo) {
    delete toggleInfo;
  }

  __declspec(dllexport) ToggleInformationPtr Toggle_Information(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      auto info = Find(element)->As<TogglePattern^>(TogglePattern::Pattern)->Current;
      return new ToggleInformation(info.ToggleState.ToString());
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return NULL;
    }
  }

  __declspec(dllexport) void Toggle(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      Find(element)->As<TogglePattern^>(TogglePattern::Pattern)->Toggle();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }
}