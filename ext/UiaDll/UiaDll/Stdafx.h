// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <Windows.h>

using namespace System;
using namespace UIA::Helper;

#include "StringHelper.h"
#include "ArrayHelper.h"

typedef enum {
    Handle = 1,
    Id,
    Value,
    Focus,
    ScreenPoint
} FindMethod;

typedef struct _ElementInformation {
  int nativeWindowHandle;
  int* runtimeId;
  int runtimeIdLength;
  char* name;

  _ElementInformation() {
    name = NULL;
  }

  _ElementInformation(Element^ element) {
    this->name = StringHelper::ToUnmanaged(element->Name);

    runtimeId = new int[element->RuntimeId->Length];
    auto index = 0;
    for each(auto id in element->RuntimeId) {
      runtimeId[index++] = id;
    }
    runtimeIdLength = element->RuntimeId->Length;
  }

  ~_ElementInformation() {
    Console::WriteLine("Releasing {0}...", gcnew String(name));

    if( NULL != name) {
      delete[] name;
    }
    if( NULL != runtimeId ) {
      delete[] runtimeId;
    }
  }

} ElementInformation, *PElementInformation;

typedef struct _Elements {
  int length;
  ElementInformation* elements;

  _Elements(array<Element^>^ elements) {
    length = elements->Length;
    this->elements = NULL;
    if( length > 0 ) {
      this->elements = new ElementInformation[length];

      auto index = 0;
      for each(Element^ child in elements) {
        auto element = new ElementInformation(child);
        memcpy(&this->elements[index++], element, sizeof(ElementInformation));
      }
    }
  }

  ~_Elements() {
    Console::WriteLine("Releasing {0} elements...", length);
    for(auto index = 0; index < length; ++index) {
      elements[index].~_ElementInformation();
    }
  }
} Elements, *PElements;

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