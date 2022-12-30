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
      int selectedItemCount = 0;

      auto selectedElements = ElementFrom(element)->Find(TreeScope::Children, gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::ListItem));
      if (selectedElements->Length == 0)
      {
        selectedElements = ElementFrom(element)->Find(TreeScope::Descendants, gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::TreeItem));
      }

      if (selectedElements->Length > 0)
      {
        for each (auto item in selectedElements)
        {
          if (item->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->Current.IsSelected)
          {
            selectedItemCount++;
          }
        }

        auto selectedItems = new _ElementInformation[selectedItemCount];
        int i = 0;
        for each (auto item in selectedElements)
        {
          if (item->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->Current.IsSelected)
          {
            selectedItems[i].Refresh(item);
            i++;
          }
        }
        *selections = selectedItems;
      }
      else
      {
        *selections = nullptr;
      }

      return selectedItemCount;
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
      return 0;
    }
  }
}
