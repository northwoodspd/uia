#include "Stdafx.h"

using namespace UIA::Helper;

extern "C" {
  __declspec(dllexport) void Mouse_Drag(const int startX, const int startY, const int endX, const int endY, char* errorInformation, const int errorInformationLength) {
    try {
      Mouse::Drag(startX, startY, endX, endY);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInformation, errorInformationLength);
    }
  }
}