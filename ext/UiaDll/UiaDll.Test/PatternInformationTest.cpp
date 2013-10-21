#include "stdafx.h"

#include <PatternInformationStructures.h>

TEST(ValueInformation, ItCleansUpAfterItself)
{
  auto valueInfo = new ValuePatternInformation("Whatever", true);
  ASSERT_STREQ("Whatever", valueInfo->Value);
  ASSERT_EQ(true, valueInfo->IsReadOnly);
  delete valueInfo;
}

TEST(ToggleInformation, ItCleansUpAfterItself)
{
  auto toggleInfo = new ToggleInformation("On");
  ASSERT_STREQ("On", toggleInfo->ToggleState);
  delete toggleInfo;
}