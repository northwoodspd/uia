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
  bool isVisible;

  _ElementInformation() : name(NULL), nativeWindowHandle(0), runtimeId(NULL), patterns(NULL), id(NULL), className(NULL) {}

  _ElementInformation(Element^ element) : name(NULL), nativeWindowHandle(0), runtimeId(NULL), patterns(NULL), id(NULL), className(NULL) {
    Refresh(element);
  }

  static _ElementInformation* From(Element^ element) {
    return nullptr != element ? new _ElementInformation(element) : NULL;
  }

  static _ElementInformation* From(...array<Element^>^ elements) {
    if( nullptr == elements || elements->Length == 0 ) return NULL;

    auto elementInformation = new _ElementInformation[elements->Length];
    auto index = 0;
    for each(auto element in elements) {
      elementInformation[index++].Refresh(element);
    }

    return elementInformation;
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
    isVisible = element->IsVisible;
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
