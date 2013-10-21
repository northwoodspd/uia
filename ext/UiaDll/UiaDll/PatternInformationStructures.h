#pragma once

#include "StringHelper.h"
using namespace System::Windows::Automation;

typedef struct _ValuePatternInformation {
  bool IsReadOnly;
  char* Value;

  _ValuePatternInformation(String^ value, bool IsReadOnly) {
    init(value, IsReadOnly);
  }

  _ValuePatternInformation(ValuePattern::ValuePatternInformation^ info) {
    init(info->Value, info->IsReadOnly);
  }

  ~_ValuePatternInformation() {
    delete[] Value;
  }

private:
  void init(String^ value, bool IsReadOnly) {
    this->IsReadOnly = IsReadOnly;
    Value = StringHelper::ToUnmanaged(value);
  }

} ValuePatternInformation, *PValuePatternInformation;

typedef struct _ToggleInformation {
  char* ToggleState;

  _ToggleInformation(String^ toggleState) {
    ToggleState = StringHelper::ToUnmanaged(toggleState);
  }

  ~_ToggleInformation() {
    delete[] ToggleState;
  }

} ToggleInformation, *PToggleInformation;
