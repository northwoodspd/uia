#include "stdafx.h"

#include <PatternInformationStructures.h>
#include "ElementStub.h"

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