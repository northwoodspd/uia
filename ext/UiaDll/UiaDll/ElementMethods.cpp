#include "Stdafx.h"

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

  __declspec(dllexport) ElementInformationPtr Element_FindById(const char* automationId, char* errorInfo, const int errorLength) {
    try {
      return ElementInformation::From(Element::ById(gcnew String(automationId)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) ElementInformationPtr Element_FindChildById(ElementInformationPtr parent, const char* automationId, const char* treeScope, char* errorInfo, const int errorLength) {
    try {
      auto scope = (TreeScope) Enum::Parse(TreeScope::typeid, gcnew String(treeScope));
      return ElementInformation::From(Find(parent)->ChildById(gcnew String(automationId), scope));
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

  __declspec(dllexport) ElementInformationPtr Element_FindChildByName(ElementInformationPtr parent, const char* name, const char* treeScope, char* errorInfo, const int errorLength) {
    try {
      auto scope = (TreeScope) Enum::Parse(TreeScope::typeid, gcnew String(treeScope));
      return ElementInformation::From(Find(parent)->ChildByName(gcnew String(name), scope));
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

  __declspec(dllexport) void Element_Click(ElementInformationPtr element, char* errorInfo, const int errorLength) {
    try {
      Find(element)->MouseClick();
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