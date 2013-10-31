#pragma once
#include "ArrayHelper.h"
#include "StringHelper.h"

typedef struct _ElementInformation {
  int nativeWindowHandle;
  int* runtimeId;
  int runtimeIdLength;
  char* name;
  char* className;
  int controlTypeId;
  int* patterns;
  int patternsLength;
  char* id;

  bool isEnabled;

  _ElementInformation() : name(NULL), nativeWindowHandle(0), runtimeId(NULL), patterns(NULL), id(NULL), className(NULL) {}

  _ElementInformation(Element^ element) : name(NULL), nativeWindowHandle(0), runtimeId(NULL), patterns(NULL), id(NULL), className(NULL) {
    Refresh(element);
  }

  static _ElementInformation* From(Element^ element) {
    return nullptr != element ? new _ElementInformation(element) : NULL;
  }

  void Refresh(Element^ element) {
    Reset();
    id = StringHelper::ToUnmanaged(element->Id);
    name = StringHelper::ToUnmanaged(element->Name);
    className = StringHelper::ToUnmanaged(element->ClassName);
    nativeWindowHandle = element->NativeWindowHandle;
    runtimeId = ArrayHelper::FromArray(element->RuntimeId);
    runtimeIdLength = element->RuntimeId->Length;
    controlTypeId = element->ControlTypeId;
    patterns = ArrayHelper::FromArray(element->SupportedPatternIds);
    patternsLength = element->SupportedPatternIds->Length;

    isEnabled = element->IsEnabled;
  }

  ~_ElementInformation() {
    Reset();
  }

private:
  void Reset() {
    delete[] name; delete[] runtimeId; delete[] patterns; delete[] id; delete[] className;
    name = NULL; runtimeId = NULL; patterns = NULL; id = NULL; className = NULL;
  }

} ElementInformation, *ElementInformationPtr;

typedef struct _Elements {
  int length;
  ElementInformation* elements;

  _Elements() : length(0), elements(NULL) {}

  _Elements(array<Element^>^ elements) : length(0), elements(NULL) {
    if( nullptr == elements ) return;

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