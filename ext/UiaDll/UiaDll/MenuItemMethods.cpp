#include "Stdafx.h"

extern "C" {
  public ref class MenuItemNotFound : Exception {
  public:
    MenuItemNotFound(String^ message) : Exception(message) {}
  };

  void SelectMenuItemPath(ElementInformationPtr, char*, const int, list<const char*>&);
  ElementInformationPtr MenuItemByPath(ElementInformationPtr element, char*, const int, list<const char*>& items);
  Element^ MenuItemPath(ElementInformationPtr, list<const char*>&);

  __declspec(dllexport) ElementInformationPtr MenuItem_ByPath(ElementInformationPtr element, char* errorInfo, const int errorInfoLength, const int n, const char* arg0, ...) {
    GRAB_VARARGS(menuItems, const char*, n);
    return MenuItemByPath(element, errorInfo, errorInfoLength, menuItems);
  }

  __declspec(dllexport) void MenuItem_SelectPath(ElementInformationPtr element, char* errorInfo, const int errorInfoLength, const int n, const char* arg0, ...) {
    GRAB_VARARGS(menuItems, const char*, n);
    SelectMenuItemPath(element, errorInfo, errorInfoLength, menuItems);
  }

  void SelectMenuItemPath(ElementInformationPtr element, char* errorInfo, const int errorInfoLength, list<const char*>& items) {
    try {
      MenuItemPath(element, items)->As<InvokePattern^>(InvokePattern::Pattern)->Invoke();
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
    }
  }

  ElementInformationPtr MenuItemByPath(ElementInformationPtr element, char* errorInfo, const int errorInfoLength, list<const char*>& items) {
    try {
      return ElementInformation::From(MenuItemPath(element, items));
    } catch(MenuItemNotFound^) {
      return NULL;
    } catch(Exception^ e) { 
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
      return NULL;
    }
  }

  void OpenMenuToCreateChildControls(ElementInformationPtr element)
  {
    auto firstItem = ElementFrom(element)->FirstMenuItem();
    if (nullptr != firstItem)
    {
      try 
      {
        auto asExpand = firstItem->As<ExpandCollapsePattern^>(ExpandCollapsePattern::Pattern);
        if (asExpand->Current.ExpandCollapseState == ExpandCollapseState::Collapsed)
        {
          asExpand->Expand();
        }
      }
      catch (Exception^)
      {}
    }
  }

  Element^ MenuItemPath(ElementInformationPtr element, list<const char*>& items) {
    auto current = ElementFrom(element);
    bool foundAtleastOneItem = false;

    for(auto item = items.begin(); item != items.end(); ++item) {
      auto name = gcnew String(*item);

      current = current->MenuItem(name);

      if (nullptr == current && !foundAtleastOneItem)
      {
        OpenMenuToCreateChildControls(element);

        current = ElementFrom(element)->MenuItem(name);
      }

      if (nullptr == current)
      {
        throw gcnew MenuItemNotFound(String::Format("the menu item \"{0}\" was not found", name));
      }

      foundAtleastOneItem = true;

      if( *item != items.back() ) {
        current->As<InvokePattern^>(InvokePattern::Pattern)->Invoke();
      }
    }

    return current;
  }
}
