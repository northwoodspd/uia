#include "Stdafx.h"

#include "ConditionHelper.h"
using namespace UIA::Helper;

extern "C" {
  Element^ ElementFrom(ElementInformationPtr element) {
    Element^ foundElement = nullptr;

    try {
      if( element->handle > 0 ) {
        foundElement = Element::ByHandle(IntPtr(element->handle));
      } else {
        foundElement = Element::ByRuntimeId(ArrayHelper::ToArray(element->runtimeId, element->runtimeIdLength));
      }
    } catch(Exception^) { }

    if( nullptr == foundElement ) {
      throw gcnew Exception(String::Format("Element no longer exists ({0})", element->ToManagedString()));
    }

    return foundElement;
  }
  __declspec(dllexport) void Element_Release(ElementInformationPtr elementInformation) {
    delete elementInformation;
  }

  __declspec(dllexport) void Element_Refresh(ElementInformationPtr element, char* errorInfo, const int errorInfoLength) {
    try {
      element->Refresh(ElementFrom(element));
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
    }
  }

  __declspec(dllexport) void Element_SendKeys(ElementInformationPtr element, const char* keysToSend, char* errorInfo, const int errorInfoLength) {
    try {
      ElementFrom(element)->SendKeys(gcnew String(keysToSend));
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
    }
  }

  ElementInformationPtr ManagedFindFirst(ElementInformationPtr element, const char* treeScope, list<SearchConditionPtr>& conditions, char* errorInfo, const int errorInfoLength) {
    try {
      auto scope = (TreeScope) Enum::Parse(TreeScope::typeid, gcnew String(treeScope));
      return ElementInformation::From(ElementFrom(element)->FindFirst(scope, ConditionHelper::ConditionFrom(conditions)));
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
    }

    return NULL;
  }

#pragma managed(push, off)
  __declspec(dllexport) ElementInformationPtr FindFirst(ElementInformationPtr element, const char* treeScope, char* errorInfo, const int errorInfoLength, const int count, SearchConditionPtr arg0, ...) {
    GRAB_VARARGS(conditions, SearchConditionPtr, count);
    return ManagedFindFirst(element, treeScope, conditions, errorInfo, errorInfoLength);
  }
#pragma managed(pop)

  int ManagedFindAll(ElementInformationPtr element, ElementInformation** elements, const char* treeScope, list<SearchConditionPtr>& conditions, char* errorInfo, const int errorInfoLength) {
    try {
      auto scope = (TreeScope) Enum::Parse(TreeScope::typeid, gcnew String(treeScope));
      auto foundElements = ElementFrom(element)->Find(scope, ConditionHelper::ConditionFrom(conditions));
      *elements = ElementInformation::From(foundElements);
      return foundElements->Length;
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
    }

    return 0;
  }

#pragma managed(push, off)
  __declspec(dllexport) int FindAll(ElementInformationPtr parent, ElementInformation** elements, const char* treeScope, char* errorInfo, const int errorInfoLength, const int count, SearchConditionPtr arg0, ...) {
    GRAB_VARARGS(conditions, SearchConditionPtr, count);
    return ManagedFindAll(parent, elements, treeScope, conditions, errorInfo, errorInfoLength);
  }
#pragma managed(pop)

  __declspec(dllexport) ElementInformationPtr Element_FindById(const char* automationId, char* errorInfo, const int errorLength) {
    try {
      return ElementInformation::From(Element::ById(gcnew String(automationId)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) ElementInformationPtr Element_FindByName(const char* name, char* errorInfo, const int errorLength) {
    try {
      return ElementInformation::From(Element::ByName(gcnew String(name)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) ElementInformationPtr Element_FindByProcessId(const int processId, char* errorInfo, const int errorLength) {
    try {
      return ElementInformation::From(Element::ByProcessId(processId));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) ElementInformationPtr Element_FindByHandle(HWND windowHandle, char* errorInfo, const int errorLength) {
    try {
      return new ElementInformation(Element::ByHandle(IntPtr(windowHandle)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) ElementInformationPtr Element_FindByRuntimeId(const int runtimeIds[], const int numberOfIds, char* errorInfo, const int errorLength) {
    try {
      return ElementInformation::From(Element::ByRuntimeId(ArrayHelper::ToArray(runtimeIds, numberOfIds)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) int Root_Children(ElementInformation** children, char* errorInfo, const int errorInfoLength) {
    try {
      auto windows = Element::Windows;
      *children = ElementInformation::From(windows);
      return windows->Length;
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
      return 0;
    }
  }

  __declspec(dllexport) int Element_Children(ElementInformationPtr parentElement, ElementInformation** children, char* errorInfo, const int errorLength) {
    try {
      auto elements = ElementFrom(parentElement)->Children;
      *children = ElementInformation::From(elements);
      return elements->Length;
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error, errorInfo, errorLength);
      return 0;
    }
  }

  __declspec(dllexport) int Element_Descendants(ElementInformationPtr parentElement, ElementInformation** descendants, char* errorInfo, const int errorLength) {
    try {
      auto elements = ElementFrom(parentElement)->Descendants;
      *descendants = ElementInformation::From(elements);
      return elements->Length;
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error, errorInfo, errorLength);
      return 0;
    }
  }

  __declspec(dllexport) void Element_ClickClickablePoint(ElementInformationPtr element, char* errorInfo, const int errorLength) {
    try {
      ElementFrom(element)->ClickClickablePoint();
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error, errorInfo, errorLength);
    }
  }

  __declspec(dllexport) void Element_ClickCenter(ElementInformationPtr element, char* errorInfo, const int errorLength) {
    try {
      ElementFrom(element)->ClickCenter();
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error, errorInfo, errorLength);
    }
  }

  __declspec(dllexport) void Element_Focus(ElementInformationPtr element, char* errorInfo, const int errorLength) {
    try {
      ElementFrom(element)->SetFocus();
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error, errorInfo, errorLength);
    }
  }

}