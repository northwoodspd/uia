#include "stdafx.h"

#include <PatternInformationStructures.h>
#include "ElementStub.h"

using namespace System::Windows::Automation;

TEST(ValueInformation, CanBeInitialized)
{
  auto valueInfo = new ValuePatternInformation("Whatever", true);
  ASSERT_STREQ("Whatever", valueInfo->Value);
  ASSERT_EQ(true, valueInfo->IsReadOnly);
  delete valueInfo;
}

TEST(ToggleInformation, CanBeInitialized)
{
  auto toggleInfo = new ToggleInformation("On");
  ASSERT_STREQ("On", toggleInfo->ToggleState);
  delete toggleInfo;
}

TEST(SelectionItemInformation, CanBeInitialized)
{
  auto isSelected = true;
  auto container = gcnew ElementStub("Expected container");

  auto selectionItemInfo = SelectionItemInformation(isSelected, container);

  ASSERT_STREQ("Expected container", selectionItemInfo.Container->name);
  ASSERT_EQ(true, selectionItemInfo.IsSelected);
}

TEST(ExpandCollapseInfo, CanBeInitialized) {
  auto expandCollapseInfo = ExpandCollapseInfo("Collapsed");
  ASSERT_STREQ("Collapsed", expandCollapseInfo.ExpandCollapseState);
}

TEST(WindowInformation, CanBeInitialized) {
  auto windowInformation = WindowInformation(WindowVisualState::Minimized, WindowInteractionState::Closing);
  ASSERT_STREQ("Minimized", windowInformation.VisualState);
  ASSERT_STREQ("Closing", windowInformation.InteractionState);
}

TEST(TableInformation, NullHeadersYieldsEmptyElements) {
  auto tableInformation = TableInformation(0, 0, nullptr);
  ASSERT_EQ(0, tableInformation.Headers->length);
}
