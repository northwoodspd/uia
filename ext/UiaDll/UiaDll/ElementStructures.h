#pragma once
#include "ArrayHelper.h"
#include "StringHelper.h"

typedef struct _ElementInformation {
  int nativeWindowHandle;
  int* runtimeId;
  int runtimeIdLength;
  char* name;
  int controlTypeId;

  _ElementInformation() : name(NULL), nativeWindowHandle(0), runtimeId(NULL) {}

  _ElementInformation(Element^ element) : name(NULL), nativeWindowHandle(0), runtimeId(NULL) {
    Update(element);
  }

  void Update(Element^ element) {
    Reset();
    name = StringHelper::ToUnmanaged(element->Name);
    nativeWindowHandle = element->NativeWindowHandle;
    runtimeId = ArrayHelper::FromArray(element->RuntimeId);
    runtimeIdLength = element->RuntimeId->Length;
    controlTypeId = element->ControlTypeId;
  }

  ~_ElementInformation() {
    Reset();
  }

private:
  void Reset() {
    delete[] name; delete[] runtimeId;
    name = NULL; runtimeId = NULL;
  }

} ElementInformation, *PElementInformation;

typedef struct _Elements {
  int length;
  ElementInformation* elements;

  _Elements() : length(0), elements(NULL) {}

  _Elements(array<Element^>^ elements) {
    length = elements->Length;
    this->elements = NULL;
    if( length > 0 ) {
      this->elements = new ElementInformation[length];
      auto index = 0;
      for each(auto element in elements) {
        this->elements[index++].Update(element);
      }
    }
  }

  ~_Elements() {
    delete[] elements;
  }
} Elements, *PElements;