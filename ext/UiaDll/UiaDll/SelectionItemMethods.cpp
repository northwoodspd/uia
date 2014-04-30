#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void SelectionItem_Release(SelectionItemInformationPtr selectionItemInfo) {
    delete selectionItemInfo;
  }

  __declspec(dllexport) SelectionItemInformationPtr SelectionItem_Information(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      auto info = ElementFrom(element)->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->Current;
      return new SelectionItemInformation(info);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return NULL;
    }
  }

  __declspec(dllexport) void SelectionItem_Select(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      ElementFrom(element)->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->Select();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }

  __declspec(dllexport) void SelectionItem_AddToSelection(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      ElementFrom(element)->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->AddToSelection();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }

  __declspec(dllexport) void SelectionItem_RemoveFromSelection(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      ElementFrom(element)->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->RemoveFromSelection();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }
}