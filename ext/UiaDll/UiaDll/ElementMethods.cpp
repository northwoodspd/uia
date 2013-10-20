#include "Stdafx.h"

using namespace UIA::Helper;

extern "C" {
  Element^ Find(PElementInformation element) {
    if( element->nativeWindowHandle > 0 ) {
      return Element::ByHandle(IntPtr(element->nativeWindowHandle));
    }

    return Element::ByRuntimeId(ArrayHelper::ToArray(element->runtimeId, element->runtimeIdLength));
  }

  __declspec(dllexport) PElementInformation Element_Root(char* errorInfo, const int errorInfoLength) {
    try {
      return new ElementInformation(Element::Root());
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorInfoLength);
      return NULL;
    }
  }

  __declspec(dllexport) void Element_Release(PElementInformation elementInformation) {
    delete elementInformation;
  }

  __declspec(dllexport) void Element_ReleaseMany(PElements elements) {
    delete elements;
  }

  __declspec(dllexport) PElementInformation Element_FindById(const char* automationId, char* errorInfo, const int errorLength) {
    try {
      return new ElementInformation(Element::ById(gcnew String(automationId)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) PElementInformation Element_FindByName(const char* name, char* errorInfo, const int errorLength) {
    try {
      return new ElementInformation(Element::ByName(gcnew String(name)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) PElementInformation Element_FindByProcessId(const int processId, char* errorInfo, const int errorLength) {
    try {
      return new ElementInformation(Element::ByProcessId(processId));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) PElementInformation Element_FindByHandle(HWND windowHandle, char* errorInfo, const int errorLength) {
    try {
      return new ElementInformation(Element::ByHandle(IntPtr(windowHandle)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) PElementInformation Element_FindByRuntimeId(const int runtimeIds[], const int numberOfIds, char* errorInfo, const int errorLength) {
    try {
      return new ElementInformation(Element::ByRuntimeId(ArrayHelper::ToArray(runtimeIds, numberOfIds)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) PElements Element_Children(PElementInformation parentElement, char* errorInfo, const int errorLength) {
    try {
      return new Elements(Find(parentElement)->Children);
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) PElements Element_ChildrenOfType(PElementInformation parent, int propertyId, char* errorInfo, const int errorLength) {
    try {
      return new Elements(Find(parent)->ChildrenOf((AutomationPropertyCondition::Id)propertyId));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) PElements Element_Descendants(PElementInformation parentElement, char* errorInfo, const int errorLength) {
    try {
      return new Elements(Find(parentElement)->Descendants);
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }

    return NULL;
  }

  __declspec(dllexport) void Element_Click(PElementInformation element, char* errorInfo, const int errorLength) {
    try {
      Find(element)->MouseClick();
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }
  }
}