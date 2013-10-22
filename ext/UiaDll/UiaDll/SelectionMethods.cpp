#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Selection_Release(PSelectionInformation selectionInfo) {
    delete selectionInfo;
  }

  __declspec(dllexport) PSelectionInformation Selection_Information(PElementInformation element, char* errorInfo, const int errorInfoLength) {
    try {
      return new SelectionInformation(Find(element)->As<SelectionPattern^>(SelectionPattern::Pattern)->Current);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return NULL;
    }
  }
}