#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) void ExpandCollapse_Release(ExpandCollapseInfoPtr expandCollapseInfo) {
    delete expandCollapseInfo;
  }

  __declspec(dllexport) ExpandCollapseInfoPtr ExpandCollapse_Information(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      auto info = ElementFrom(element)->As<ExpandCollapsePattern^>(ExpandCollapsePattern::Pattern)->Current;
      return new ExpandCollapseInfo(info.ExpandCollapseState.ToString());
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
      return NULL;
    }
  }

  __declspec(dllexport) void ExpandCollapse_Expand(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      ElementFrom(element)->As<ExpandCollapsePattern^>(ExpandCollapsePattern::Pattern)->Expand();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
    }
  }

  __declspec(dllexport) void ExpandCollapse_Collapse(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      ElementFrom(element)->As<ExpandCollapsePattern^>(ExpandCollapsePattern::Pattern)->Collapse();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
    }
  }
}