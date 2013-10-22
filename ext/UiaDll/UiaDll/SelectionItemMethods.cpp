#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void SelectionItem_Release(PSelectionItemInformation selectionItemInfo) {
    delete selectionItemInfo;
  }

  __declspec(dllexport) PSelectionItemInformation SelectionItem_Information(PElementInformation element, char* errorInfo, const int errorInfoLength) {
    try {
      auto info = Find(element)->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->Current;
      return new SelectionItemInformation(info);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }

  __declspec(dllexport) void SelectionItem_Select(PElementInformation element, char* errorInfo, const int errorInfoLength) {
    try {
      Find(element)->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->Select();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }

  __declspec(dllexport) void SelectionItem_AddToSelection(PElementInformation element, char* errorInfo, const int errorInfoLength) {
    try {
      Find(element)->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->AddToSelection();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }
}