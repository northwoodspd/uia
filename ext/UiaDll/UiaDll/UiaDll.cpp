#include "stdafx.h"
#include "DynamicAssemblyResolver.h"

extern "C" {
  __declspec(dllexport) void initialize(char* privateAssemblyDirectory) {
    DynamicAssemblyResolver::PrivatePath = gcnew String(privateAssemblyDirectory);
  }

  __declspec(dllexport) void Automation_WarmUp() {
    try {
      auto warmed = Element::Windows;
    } catch(Exception^) {}
  }
}

