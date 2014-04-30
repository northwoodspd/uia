#include "Stdafx.h"

#include "ConditionHelper.h"
using namespace UIA::Helper;

extern "C" {
  Element^ Find(ElementInformationPtr element) {
    if( element->nativeWindowHandle > 0 ) {
      return Element::ByHandle(IntPtr(element->nativeWindowHandle));
    }

    return Element::ByRuntimeId(ArrayHelper::ToArray(element->runtimeId, element->runtimeIdLength));
  }

  __declspec(dllexport) void Element_Release(ElementInformationPtr elementInformation) {
    delete elementInformation;
  }

  __declspec(dllexport) void Element_Refresh(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      element->Refresh(Find(element));
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }

  __declspec(dllexport) void Element_SendKeys(ElementInformationPtr element, const char* keysToSend, char* errorInfo, const int errorInfoLength) {
    try {
      Find(element)->SendKeys(gcnew String(keysToSend));
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }
  }

  ElementInformationPtr ManagedFindFirst(ElementInformationPtr element, const char* treeScope, list<SearchConditionPtr>& conditions, char* errorInfo, const int errorInfoLength) {
    try {
      auto scope = (TreeScope) Enum::Parse(TreeScope::typeid, gcnew String(treeScope));
      return ElementInformation::From(Find(element)->ChildWith(scope, ConditionHelper::ConditionFrom(conditions)));
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
    }

    return NULL;
  }

  __declspec(dllexport) ElementInformationPtr FindFirst(ElementInformationPtr element, const char* treeScope, char* errorInfo, const int errorInfoLength, const int count, SearchConditionPtr arg0, ...) {
    va_list arguments;
    va_start(arguments, arg0);

    list<SearchConditionPtr> conditions;
    conditions.push_back(arg0);
    for(auto index = 1; index < count; index++) {
      conditions.push_back(va_arg(arguments, SearchConditionPtr));
    }

    return ManagedFindFirst(element, treeScope, conditions, errorInfo, errorInfoLength);
  }

  int ManagedFindAllByConditions(ElementInformationPtr element, ElementInformation** elements, const char* treeScope, list<SearchConditionPtr>& conditions, char* errorInfo, const int errorInfoLength) {
    try {
      auto scope = (TreeScope) Enum::Parse(TreeScope::typeid, gcnew String(treeScope));
      auto foundElements = Find(element)->ChildrenWith(scope, ConditionHelper::ConditionFrom(conditions));
      *elements = ElementInformation::From(foundElements);
      return foundElements->Length;
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message + Environment::NewLine + e->StackTrace, errorInfo, errorInfoLength);
    }

    return 0;
  }

  __declspec(dllexport) int FindAllByConditions(ElementInformationPtr parent, ElementInformation** elements, const char* treeScope, char* errorInfo, const int errorInfoLength, const int count, SearchConditionPtr arg0, ...) {
    va_list arguments;
    va_start(arguments, arg0);

    list<SearchConditionPtr> conditions;
    conditions.push_back(arg0);
    for(auto index = 1; index < count; index++) {
      conditions.push_back(va_arg(arguments, SearchConditionPtr));
    }

    return ManagedFindAllByConditions(parent, elements, treeScope, conditions, errorInfo, errorInfoLength);
  }

  __declspec(dllexport) ElementInformationPtr Element_FindById(const char* automationId, char* errorInfo, const int errorLength) {
    try {
      return ElementInformation::From(Element::ById(gcnew String(automationId)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) ElementInformationPtr Element_FindByName(const char* name, char* errorInfo, const int errorLength) {
    try {
      return ElementInformation::From(Element::ByName(gcnew String(name)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) ElementInformationPtr Element_FindByProcessId(const int processId, char* errorInfo, const int errorLength) {
    try {
      return ElementInformation::From(Element::ByProcessId(processId));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) ElementInformationPtr Element_FindByHandle(HWND windowHandle, char* errorInfo, const int errorLength) {
    try {
      return new ElementInformation(Element::ByHandle(IntPtr(windowHandle)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) ElementInformationPtr Element_FindByRuntimeId(const int runtimeIds[], const int numberOfIds, char* errorInfo, const int errorLength) {
    try {
      return ElementInformation::From(Element::ByRuntimeId(ArrayHelper::ToArray(runtimeIds, numberOfIds)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) int Root_Children(ElementInformation** children, char* errorInfo, const int errorInfoLength) {
    try {
      auto windows = Element::Windows;
      *children = ElementInformation::From(windows);
      return windows->Length;
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return 0;
    }
  }

  __declspec(dllexport) int Element_Children(ElementInformationPtr parentElement, ElementInformation** children, char* errorInfo, const int errorLength) {
    try {
      auto elements = Find(parentElement)->Children;
      *children = ElementInformation::From(elements);
      return elements->Length;
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
      return 0;
    }
  }

  __declspec(dllexport) int Element_Descendants(ElementInformationPtr parentElement, ElementInformation** descendants, char* errorInfo, const int errorLength) {
    try {
      auto elements = Find(parentElement)->Descendants;
      *descendants = ElementInformation::From(elements);
      return elements->Length;
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
      return 0;
    }
  }

  __declspec(dllexport) void Element_ClickClickablePoint(ElementInformationPtr element, char* errorInfo, const int errorLength) {
    try {
      Find(element)->ClickClickablePoint();
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }
  }

  __declspec(dllexport) void Element_ClickCenter(ElementInformationPtr element, char* errorInfo, const int errorLength) {
    try {
      Find(element)->ClickCenter();
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }
  }

  __declspec(dllexport) void Element_Focus(ElementInformationPtr element, char* errorInfo, const int errorLength) {
    try {
      Find(element)->SetFocus();
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }
  }

}