#include "Stdafx.h"

using namespace UIA::Helper;

extern "C" {
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

  __declspec(dllexport) PElementInformation Element_FindByRuntimeId(const int runtimeIds[], const int numberOfIds, char* errorInfo, const int errorLength) {
    try {
      return new ElementInformation(Element::ByRuntimeId(ArrayHelper::ToArray(runtimeIds, numberOfIds)));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }
  }

  __declspec(dllexport) PElements Element_Children(PElementInformation parentElement, char* errorInfo, const int errorLength) {
    try {
      auto foundChildren = Element::ByRuntimeId(ArrayHelper::ToArray(parentElement->runtimeId, parentElement->runtimeIdLength))->Children;
      return new Elements(foundChildren);
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }
  }

  __declspec(dllexport) void Element_Click(PElementInformation element, char* errorInfo, const int errorLength) {
    try {
      Element::ByRuntimeId(ArrayHelper::ToArray(element->runtimeId, element->runtimeIdLength))->MouseClick();
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }
  }
}