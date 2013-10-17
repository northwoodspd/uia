#include "stdafx.h"
#include <StringHelper.h>

TEST(StringHelper, ItCanConvertToUnmanagedStrings)
{
  auto unmanaged = StringHelper::ToUnmanaged("Expected");
  ASSERT_STREQ("Expected", unmanaged);
  delete[] unmanaged;
}

TEST(StringHelper, NullStringYieldsNullUnmanagedString)
{
  ASSERT_EQ(NULL, StringHelper::ToUnmanaged(nullptr));
}