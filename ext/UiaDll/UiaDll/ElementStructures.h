#include "Stdafx.h"

typedef struct _ElementInformation {
  int nativeWindowHandle;
  int* runtimeId;
  int runtimeIdLength;
  char* name;
  int controlTypeId;

  _ElementInformation() : name(NULL), nativeWindowHandle(0) {}

  _ElementInformation(Element^ element) : name(NULL), nativeWindowHandle(0) {
    this->name = StringHelper::ToUnmanaged(element->Name);
    this->nativeWindowHandle = element->NativeWindowHandle;
    runtimeId = ArrayHelper::FromArray(element->RuntimeId);
    runtimeIdLength = element->RuntimeId->Length;
    controlTypeId = element->ControlTypeId;
  }

  ~_ElementInformation() {
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
    for(auto index = 0; index < length; ++index) {
      elements[index].~_ElementInformation();
    }
  }
} Elements, *PElements;