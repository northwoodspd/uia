#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Table_Release(TableInformationPtr tableInfo) {
    delete tableInfo;
  }

  __declspec(dllexport) TableInformationPtr Table_Information(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      return new TableInformation(Find(element)->As<TablePattern^>(TablePattern::Pattern)->Current);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return NULL;
    }
  }
}