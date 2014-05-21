#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void Table_Release(TableInformationPtr tableInfo) {
    delete tableInfo;
  }

  __declspec(dllexport) TableInformationPtr Table_Information(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      return new TableInformation(ElementFrom(element)->As<TablePattern^>(TablePattern::Pattern)->Current);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
      return NULL;
    }
  }

  __declspec(dllexport) int Table_Headers(ElementInformationPtr element, ElementInformation** headers, char* errorInfo, const int errorInfoLength) {
    try {
      auto headerElements = ElementFrom(element)->As<TablePattern^>(TablePattern::Pattern)->Current.GetColumnHeaders();
      *headers = ElementInformation::From(Element::From(headerElements));
      return headerElements->Length;
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
      return 0;
    }
  }

  __declspec(dllexport) ElementInformationPtr Table_Row(ElementInformationPtr element, const int index, char* errorInfo, const int errorInfoLength) {
    try {
      auto table = ElementFrom(element);
      return ElementInformation::From(table->Find(TreeScope::Children, gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::DataItem))[index]);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
      return NULL;
    }
  }
}