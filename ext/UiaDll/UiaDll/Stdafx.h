// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <Windows.h>

using namespace System;
using namespace UIA::Helper;

#include "StringHelper.h"

typedef enum {
    Handle = 1,
    Id,
    Value,
    Focus,
    ScreenPoint
} FindMethod;

typedef struct _ElementInformation {
  char* name;

  _ElementInformation() {
    name = NULL;
  }

  _ElementInformation(Element^ element) {
    this->name = StringHelper::ToUnmanaged(element->Name);
  }

  ~_ElementInformation() {
    if( NULL != name) {
      Console::WriteLine("Woohoo! It's being free'd! ({0})", gcnew String(name));
      delete[] name;
    }
  }

} ElementInformation, *PElementInformation;

typedef struct _FindInformation {
    HWND rootWindow;
    int index;
    bool onlySearchChildren;
    FindMethod  how;
    union {
        char stringData[256];
        int intData;
        int pointData[2];
	  } data;
} FindInformation, *LPFindInformation;