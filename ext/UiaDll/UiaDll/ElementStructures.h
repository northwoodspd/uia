#include "Stdafx.h"

typedef struct _ElementInformation {
  int nativeWindowHandle;
  int* runtimeId;
  int runtimeIdLength;
  char* name;

  _ElementInformation() : name(NULL), nativeWindowHandle(0) {}

  _ElementInformation(Element^ element) : name(NULL), nativeWindowHandle(0) {
    this->name = StringHelper::ToUnmanaged(element->Name);
    this->nativeWindowHandle = element->NativeWindowHandle;

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