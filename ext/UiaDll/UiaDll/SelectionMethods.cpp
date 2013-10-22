#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Selection_Release(SelectionInformationPtr selectionInfo) {
    delete selectionInfo;
  }

  __declspec(dllexport) SelectionInformationPtr Selection_Information(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      return new SelectionInformation(Find(element)->As<SelectionPattern^>(SelectionPattern::Pattern)->Current);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return NULL;
    }
  }
}