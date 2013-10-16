#include "stdafx.h"
#include "ElementStub.h"
#include <ElementStructures.h>

class ElementInformationTest : public ::testing::Test {
public:
  Element^ ElementWith(String^ name) {
    return gcnew ElementStub(name);
  }

  Element^ ElementWith(...array<int>^ runtimeIds) {
    return gcnew ElementStub("", runtimeIds);
  }
};

TEST_F(ElementInformationTest, ItCleansUpTheName)
{
  auto elementInformation = new ElementInformation(ElementWith("Some Name"));
  delete elementInformation;
}

TEST_F(ElementInformationTest, ItCleansUpTheRuntimeId)
{
  auto elementInformation = new ElementInformation(ElementWith(46, 2));
  delete elementInformation;
}

TEST_F(ElementInformationTest, ItHasTheName)
{
  ASSERT_STREQ("Expected Name", ElementInformation(gcnew ElementStub("Expected Name")).name);
}

TEST_F(ElementInformationTest, ItKnowsAboutTheRuntimeId)
{
  auto elementInformation = ElementInformation(gcnew ElementStub("", 0, 1, 2));
  for(auto expected = 0; expected < 3; expected++) {
    ASSERT_EQ(expected, elementInformation.runtimeId[expected]);
  }

  ASSERT_EQ(3, elementInformation.runtimeIdLength);
}

TEST_F(ElementInformationTest, ItKnowsTheWindowHandle)
{
  auto element = gcnew ElementStub("");
  element->NativeWindowHandle = 12345;

  ASSERT_EQ(ElementInformation(element).nativeWindowHandle, 12345);
}

TEST_F(ElementInformationTest, ItKnowsTheControlType)
{
  auto element = gcnew ElementStub("");
  element->ControlTypeId = 1234;

  ASSERT_EQ(1234, ElementInformation(element).controlTypeId);
}

TEST_F(ElementInformationTest, ItCanBeUpdated)
{
  auto elementInformation = ElementInformation(gcnew ElementStub("Initial", 0));

  auto updatedElement = gcnew ElementStub("Updated", 46, 2);
  updatedElement->NativeWindowHandle = 123;
  elementInformation.Update(updatedElement);

  ASSERT_STREQ("Updated", elementInformation.name);
  ASSERT_EQ(46, elementInformation.runtimeId[0]);
  ASSERT_EQ(2, elementInformation.runtimeId[1]);
  ASSERT_EQ(123, elementInformation.nativeWindowHandle);
}
