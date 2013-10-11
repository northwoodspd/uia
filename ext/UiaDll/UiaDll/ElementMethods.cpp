#include "Stdafx.h"

using namespace UIA::Helper;

extern "C" {
  __declspec(dllexport) void Element_Release(PElementInformation elementInformation) {
    delete elementInformation;
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
      auto ids = gcnew array<int>(numberOfIds);
      for(auto index = 0; index < numberOfIds; ++index) {
        ids[index] = runtimeIds[index];
      }

      return new ElementInformation(Element::ByRuntimeId(ids));
    } catch(Exception^ error) {
      StringHelper::CopyToUnmanagedString(error->Message, errorInfo, errorLength);
    }
  }
}