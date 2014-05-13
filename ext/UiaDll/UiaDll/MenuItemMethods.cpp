#include "Stdafx.h"

extern "C" {
  void SelectMenuItemPath(ElementInformationPtr element, char* errorInfo, const int errorInfoLength, list<const char*>& items) {
    try {
      auto current = ElementFrom(element);

      for(auto item = items.begin(); item != items.end(); ++item) {
        auto name = gcnew String(*item);

        current = current->MenuItem(name);
        if( nullptr == current) {
          throw gcnew Exception(String::Format("the menu item \"{0}\" was not found", name));
        }

        current->As<InvokePattern^>(InvokePattern::Pattern)->Invoke();
      }
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }

  __declspec(dllexport) void MenuItem_SelectPath(ElementInformationPtr element, char* errorInfo, const int errorInfoLength, const int n, const char* arg0, ...) {
    GRAB_VARARGS(menuItems, const char*, n);
    SelectMenuItemPath(element, errorInfo, errorInfoLength, menuItems);
  }
}