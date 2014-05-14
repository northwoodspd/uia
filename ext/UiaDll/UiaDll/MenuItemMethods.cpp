#include "Stdafx.h"

extern "C" {
  public ref class MenuItemNotFound : Exception {
  public:
    MenuItemNotFound(String^ message) : Exception(message) {}
  };

  void SelectMenuItemPath(ElementInformationPtr, char*, const int, list<const char*>&);
  bool HasMenuItemPath(ElementInformationPtr, char*, const int, list<const char*>&);
  InvokePattern^ MenuItemPath(ElementInformationPtr, list<const char*>&);

  __declspec(dllexport) bool MenuItem_HasPath(ElementInformationPtr element, char* errorInfo, const int errorInfoLength, const int n, const char* arg0, ...) {
    GRAB_VARARGS(menuItems, const char*, n);
    return HasMenuItemPath(element, errorInfo, errorInfoLength, menuItems);
  }

  __declspec(dllexport) void MenuItem_SelectPath(ElementInformationPtr element, char* errorInfo, const int errorInfoLength, const int n, const char* arg0, ...) {
    GRAB_VARARGS(menuItems, const char*, n);
    SelectMenuItemPath(element, errorInfo, errorInfoLength, menuItems);
  }

  void SelectMenuItemPath(ElementInformationPtr element, char* errorInfo, const int errorInfoLength, list<const char*>& items) {
    try {
      MenuItemPath(element, items)->Invoke();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }

  bool HasMenuItemPath(ElementInformationPtr element, char* errorInfo, const int errorInfoLength, list<const char*>& items) {
    try {
      return nullptr != MenuItemPath(element, items);
    } catch(MenuItemNotFound^) {
      return false;
    } catch(Exception^ e) { 
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return false;
    }
  }

  InvokePattern^ MenuItemPath(ElementInformationPtr element, list<const char*>& items) {
    auto current = ElementFrom(element);

    for(auto item = items.begin(); item != items.end(); ++item) {
      auto name = gcnew String(*item);

      current = current->MenuItem(name);
      if( nullptr == current) {
        throw gcnew MenuItemNotFound(String::Format("the menu item \"{0}\" was not found", name));
      }

      if( *item != items.back() ) {
        current->As<InvokePattern^>(InvokePattern::Pattern)->Invoke();
      }
    }

    return current->As<InvokePattern^>(InvokePattern::Pattern);
  }
}