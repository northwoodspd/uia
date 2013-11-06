#pragma once

#include "StringHelper.h"
#include "ElementStructures.h"

using namespace System;
using namespace System::Linq;
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

} ValuePatternInformation, *ValuePatternInformationPtr;

typedef struct _ToggleInformation {
  char* ToggleState;

  _ToggleInformation(String^ toggleState) {
    ToggleState = StringHelper::ToUnmanaged(toggleState);
  }

  ~_ToggleInformation() {
    delete[] ToggleState;
  }

} ToggleInformation, *ToggleInformationPtr;

typedef struct _SelectionInformation {
  bool CanSelectMultiple;
  bool IsSelectionRequired;

  _SelectionInformation(SelectionPattern::SelectionPatternInformation^ info) {
    CanSelectMultiple = info->CanSelectMultiple;
    IsSelectionRequired = info->IsSelectionRequired;
  }
} SelectionInformation, *SelectionInformationPtr;

typedef struct _SelectionItemInformation {
  bool IsSelected;
  ElementInformationPtr Container;

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

} SelectionItemInformation, *SelectionItemInformationPtr;


typedef struct _ExpandCollapseInfo {
  char* ExpandCollapseState;

  _ExpandCollapseInfo(String^ expandCollapseState) {
    ExpandCollapseState = StringHelper::ToUnmanaged(expandCollapseState);
  }
  
  ~_ExpandCollapseInfo() {
    delete[] ExpandCollapseState;
  }
} ExpandCollapseInfo, *ExpandCollapseInfoPtr;

typedef struct _WindowInformation {
  char* VisualState;
  char* InteractionState;
  bool CanMinimize;
  bool CanMaximize;
  bool IsModal;
  bool IsTopmost;

  _WindowInformation(WindowVisualState visualState, WindowInteractionState interactionState) {
    init(visualState, interactionState);
  }

  _WindowInformation(WindowPattern::WindowPatternInformation^ windowInformation) {
    init(windowInformation->WindowVisualState, windowInformation->WindowInteractionState);
    CanMinimize = windowInformation->CanMinimize;
    CanMaximize = windowInformation->CanMaximize;
    IsModal = windowInformation->IsModal;
    IsTopmost = windowInformation->IsTopmost;
  }

  ~_WindowInformation() {
    delete[] VisualState;
    delete[] InteractionState;
  }

private:
  void init(WindowVisualState visualState, WindowInteractionState interactionState) {
    VisualState = StringHelper::ToUnmanaged(visualState.ToString());
    InteractionState = StringHelper::ToUnmanaged(interactionState.ToString());
  }

} WindowInformation, *WindowInformationPtr;

typedef struct _TableInformation {
  int RowCount;
  int ColumnCount;

  _TableInformation(TablePattern::TablePatternInformation^ tableInfo) {
    RowCount = tableInfo->RowCount;
    ColumnCount = tableInfo->ColumnCount;
  }
} TableInformation, *TableInformationPtr;

typedef struct _TableItemInformation {
  int Column;
  int Row;

  _TableItemInformation(TableItemPattern::TableItemPatternInformation^ tableItemInfo) {
    Column = tableItemInfo->Column;
    Row = tableItemInfo->Row;
  }

} TableItemInformation, *TableItemInformationPtr;

typedef struct _RangeValueInformation {
  double Value;
  double Minimum;
  double Maximum;
  double SmallChange;
  double LargeChange;
  bool IsReadOnly;

  _RangeValueInformation(RangeValuePattern::RangeValuePatternInformation^ rangeValueInfo) {
    Value = rangeValueInfo->Value;
    Minimum = rangeValueInfo->Minimum;
    Maximum = rangeValueInfo->Maximum;
    SmallChange =  rangeValueInfo->SmallChange;
    LargeChange = rangeValueInfo->LargeChange;
    IsReadOnly = rangeValueInfo->IsReadOnly;
  }
} RangeValueInformation, *RangeValueInformationPtr;