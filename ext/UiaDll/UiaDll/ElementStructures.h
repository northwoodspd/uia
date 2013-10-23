#pragma once
#include "ArrayHelper.h"
#include "StringHelper.h"

typedef struct _ElementInformation {
  int nativeWindowHandle;
  int* runtimeId;
  int runtimeIdLength;
  char* name;
  int controlTypeId;
  int* patterns;
  int patternsLength;
  char* id;

  _ElementInformation() : name(NULL), nativeWindowHandle(0), runtimeId(NULL), patterns(NULL), id(NULL) {}

  _ElementInformation(Element^ element) : name(NULL), nativeWindowHandle(0), runtimeId(NULL), patterns(NULL), id(NULL) {
    Refresh(element);
  }

  static _ElementInformation* From(Element^ element) {
    return nullptr != element ? new _ElementInformation(element) : NULL;
  }

  void Refresh(Element^ element) {
    Reset();
    id = StringHelper::ToUnmanaged(element->Id);
    name = StringHelper::ToUnmanaged(element->Name);
    nativeWindowHandle = element->NativeWindowHandle;
    runtimeId = ArrayHelper::FromArray(element->RuntimeId);
    runtimeIdLength = element->RuntimeId->Length;
    controlTypeId = element->ControlTypeId;
    patterns = ArrayHelper::FromArray(element->SupportedPatternIds);
    patternsLength = element->SupportedPatternIds->Length;
  }

  ~_ElementInformation() {
    Reset();
  }

private:
  void Reset() {
    delete[] name; delete[] runtimeId; delete[] patterns; delete[] id;
    name = NULL; runtimeId = NULL; patterns = NULL; id = NULL;
  }

} ElementInformation, *ElementInformationPtr;

typedef struct _Elements {
  int length;
  ElementInformation* elements;

  _Elements() : length(0), elements(NULL) {}

  _Elements(array<Element^>^ elements) : elements(NULL) {
    length = elements->Length;
    if( length > 0 ) this->elements = new ElementInformation[length];

    auto index = 0;
    for each(auto element in elements) {
      this->elements[index++].Refresh(element);
    }
  }

  ~_Elements() {
    delete[] elements;
  }
} Elements, *ElementsPtr;