#include "stdafx.h"
#include <ElementStructures.h>

TEST(Conditions_HaveIds)
{
  auto condition = SearchCondition(123, 0);
  ASSERT_EQ(123, condition.propertyId);
}

TEST(Conditions_CanBeNumbers)
{
  auto condition = SearchCondition(0, 456);
  ASSERT_EQ(456, condition.number);
}

TEST(Conditions_CanBeStrings)
{
  auto condition = SearchCondition(0, "expected value");
  ASSERT_STREQ("expected value", condition.string);
  ASSERT_TRUE(condition.IsString());
}

TEST(Conditions_CanHaveMultipleNumbers)
{
  list<const int> numbers;
  numbers.push_back(7);
  numbers.push_back(6);

  auto condition = SearchCondition(0, numbers);
  ASSERT_EQ(2, condition.numbersCount);
  ASSERT_EQ(7, condition.numbers[0]);
  ASSERT_EQ(6, condition.numbers[1]);
  ASSERT_TRUE(condition.HasNumbers());
}
