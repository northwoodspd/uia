#include "stdafx.h"
#include "DynamicAssemblyResolver.h"

extern "C" {
  __declspec(dllexport) void initialize(char* privateAssemblyDirectory) {
    DynamicAssemblyResolver::PrivatePath = gcnew String(privateAssemblyDirectory);
  }
}

