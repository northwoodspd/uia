#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Window_Release(WindowInformationPtr windowInformation) {
    delete windowInformation;
  }

  __declspec(dllexport) WindowInformationPtr Window_Information(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      return new WindowInformation(Find(element)->As<WindowPattern^>(WindowPattern::Pattern)->Current);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return NULL;
    }
  }

  __declspec(dllexport) void Window_SetVisualState(ElementInformationPtr element, const char* visualState, char* errorInfo, const int errorInfoLength) {
    try {
      Find(element)->As<WindowPattern^>(WindowPattern::Pattern)->SetWindowVisualState((WindowVisualState) Enum::Parse(WindowVisualState::typeid, gcnew String(visualState), false));
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }
}