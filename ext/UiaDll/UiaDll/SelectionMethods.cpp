#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Selection_Release(SelectionInformationPtr selectionInfo) {
    delete selectionInfo;
  }

  __declspec(dllexport) SelectionInformationPtr Selection_Information(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      return new SelectionInformation(ElementFrom(element)->As<SelectionPattern^>(SelectionPattern::Pattern)->Current);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
      return NULL;
    }
  }

  __declspec(dllexport) int Selection_Selections(ElementInformationPtr element, ElementInformation** selections, char* errorInfo, const int errorInfoLength) {
    try {
      auto selectedElements = Element::From(ElementFrom(element)->As<SelectionPattern^>(SelectionPattern::Pattern)->Current.GetSelection());
      *selections = ElementInformation::From(selectedElements);
      return selectedElements->Length;
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
      return 0;
    }
  }
}