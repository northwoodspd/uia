#include "Stdafx.h"

extern "C" {
  __declspec(dllexport) int Text_GetText(ElementInformationPtr element, char* text, const int textLength, char* errorInfo, const int errorInfoLength) {
    try {
      auto theText = Find(element)->As<TextPattern^>(TextPattern::Pattern)->DocumentRange->GetText(-1);
      if( NULL != text ) {
        StringHelper::CopyToUnmanagedString(theText, text, textLength);
      }

      return theText->Length;
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return 0;
    }
  }
}