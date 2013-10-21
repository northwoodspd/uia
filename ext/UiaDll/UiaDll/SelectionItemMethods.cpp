#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void SelectionItem_Select(PElementInformation element, char* errorInfo, const int errorInfoLength) {
    try {
      Find(element)->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->Select();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }
}