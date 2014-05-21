#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void TableItem_Release(TableItemInformationPtr tableItemInfo) {
    delete tableItemInfo;
  }

  __declspec(dllexport) TableItemInformationPtr TableItem_Information(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      return new TableItemInformation(ElementFrom(element)->As<TableItemPattern^>(TableItemPattern::Pattern)->Current);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
      return NULL;
    }
  }
}