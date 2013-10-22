#pragma once

#include "StringHelper.h"
#include "ElementStructures.h"

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

typedef struct _SelectionInformation {
  bool CanSelectMultiple;
  bool IsSelectionRequired;

  _SelectionInformation(SelectionPattern::SelectionPatternInformation^ info) {
    CanSelectMultiple = info->CanSelectMultiple;
    IsSelectionRequired = info->IsSelectionRequired;
  }
} SelectionInformation, *PSelectionInformation;

typedef struct _SelectionItemInformation {
  bool IsSelected;
  PElementInformation Container;

  _SelectionItemInformation(SelectionItemPattern::SelectionItemPatternInformation^ info) {
    init(info->IsSelected, Element::From(info->SelectionContainer));
  }

  _SelectionItemInformation(bool isSelected, Element^ selectionContainer) { // for testing
    init(isSelected, selectionContainer);
  }

  ~_SelectionItemInformation() {
    delete Container;
  }

private:
  void init(bool isSelected, Element^ selectionContainer) {
    IsSelected = isSelected;
    Container = new ElementInformation(selectionContainer);
  }

} SelectionItemInformation, *PSelectionItemInformation;
