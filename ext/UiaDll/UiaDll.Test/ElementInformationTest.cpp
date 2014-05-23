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

TEST_F(ElementInformationTest, ItHasAnId)
{
  auto element = gcnew ElementStub("");
  element->Id = "Expected Id";
  ASSERT_STREQ("Expected Id", ElementInformation(element).id);
}

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

TEST_F(ElementInformationTest, ItHasTheHelpText) {
  auto element = gcnew ElementStub("");
  element->HelpText = gcnew String("Expected help text");

  ASSERT_STREQ("Expected help text", ElementInformation(element).helpText);
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

  ASSERT_EQ(ElementInformation(element).handle, 12345);
}

TEST_F(ElementInformationTest, ItKnowsTheControlType)
{
  auto element = gcnew ElementStub("");
  element->ControlTypeId = 1234;

  ASSERT_EQ(1234, ElementInformation(element).controlTypeId);
}

TEST_F(ElementInformationTest, ItKnowsTheClassName)
{
  auto element = gcnew ElementStub("");
  element->ClassName = "Expected class name";

  ASSERT_STREQ("Expected class name", ElementInformation(element).className);
}

TEST_F(ElementInformationTest, ItKnowsTheSupportedPatterns)
{
  auto element = gcnew ElementStub("");
  element->SetPatterns(7, 5, 3);

  auto elementInformation = ElementInformation(element);

  const int expectedPatterns[] = {7, 5, 3};
  ASSERT_THAT(expectedPatterns, ::testing::ElementsAreArray(elementInformation.patterns, elementInformation.patternsLength));
}

TEST_F(ElementInformationTest, ItKnowIfItIsEnabled)
{
  auto element = gcnew ElementStub("");
  element->IsEnabled = true;

  ASSERT_EQ(true, ElementInformation(element).isEnabled);
}

TEST_F(ElementInformationTest, ItKnowsIfItHasFocus)
{
  auto element = gcnew ElementStub("");
  element->HasKeyboardFocus = true;

  ASSERT_EQ(true, ElementInformation(element).hasKeyboardFocus);
}

TEST_F(ElementInformationTest, ItCanBeRefreshed)
{
  auto elementInformation = ElementInformation(gcnew ElementStub("Initial", 0));

  auto updatedElement = gcnew ElementStub("Refreshed", 46, 2);
  updatedElement->NativeWindowHandle = 123;
  elementInformation.Refresh(updatedElement);

  const int expectedId[] = {46, 2};
  ASSERT_THAT(expectedId, ::testing::ElementsAreArray(elementInformation.runtimeId, elementInformation.runtimeIdLength));
  ASSERT_STREQ("Refreshed", elementInformation.name);
  ASSERT_EQ(123, elementInformation.handle);
}

TEST_F(ElementInformationTest, ItCanBeInitializedFromManyElements) {
  auto elementInformation = ElementInformation::From(gcnew ElementStub("First Element", 123), gcnew ElementStub("Second Element", 456));

  ASSERT_STREQ("First Element", elementInformation[0].name);
  ASSERT_STREQ("Second Element", elementInformation[1].name);
  delete[] elementInformation;
}

TEST_F(ElementInformationTest, ItIsNullIfThereAreNoElements) {
  ASSERT_EQ(NULL, ElementInformation::From(gcnew array<Element^>(0)));

  array<Element^>^ nullElements = nullptr;
  ASSERT_EQ(NULL, ElementInformation::From(nullElements));
}

TEST_F(ElementInformationTest,  BadThingsHappenInChildren_ItCleansUpWhatItAllocated) {
  auto badElement = gcnew ElementStub("Bad element", 123);
  badElement->SetupBoundingRectangleToThrow();

  Exception^ caughtException = nullptr;

  try {
    ElementInformation::From(gcnew ElementStub("Good element", 456), badElement);
  } catch(Exception^ e) { caughtException = e; }

  ASSERT_TRUE(caughtException != nullptr);
}

TEST_F(ElementInformationTest, BadThingsHappenForSingleElement_ItCleansUp) {
  auto badElement = gcnew ElementStub("Bad element", 123);
  badElement->SetupBoundingRectangleToThrow();

  Exception^ caughtException = nullptr;

  try {
    ElementInformation::From(badElement);
  } catch(Exception^ e) { caughtException = e; }

  // should have cleaned up memory
  ASSERT_TRUE(caughtException != nullptr);
}

#define GRAB_VARARGS(argument_list, arg_type, arg_count) \
   va_list arguments;\
   va_start(arguments, arg0);\
   list<##arg_type##> ##argument_list##;\
   ##argument_list##.push_back(arg0);\
   for(auto index = 1; index < ##arg_count##; ++index) {\
     auto value = va_arg(arguments, ##arg_type##);\
     ##argument_list##.push_back(value);\
   }

#define ASSERT_EXPECTED_EL_TO_STRING(expectedValue) \
  auto length = 0; \
  auto expectedLength = strlen(expectedValue) + 1; \
  ASSERT_EQ(expectedLength, length = el.ToString(NULL, 0)); \
  auto actual = new char[expectedLength]; \
  el.ToString(actual, expectedLength); \
  ASSERT_STREQ(expectedValue, actual); \
  delete[] actual;

TEST(ElementInformation, ToString_AllEmpty)
{
  ElementInformation el;
  ASSERT_EXPECTED_EL_TO_STRING("id: (null), name: (null), handle: 0x0, runtime_id: (null)");
}

TEST(ElementInformation, ToString_HasId)
{
  ElementInformation el;
  el.id = StringHelper::ToUnmanaged("someId");
  ASSERT_EXPECTED_EL_TO_STRING("id: someId, name: (null), handle: 0x0, runtime_id: (null)");
}

TEST(ElementInformation, ToString_HasName)
{
  ElementInformation el;
  el.name = StringHelper::ToUnmanaged("someName");
  ASSERT_EXPECTED_EL_TO_STRING("id: (null), name: someName, handle: 0x0, runtime_id: (null)");
}

TEST(ElementInformation, ToString_HasHandle)
{
  ElementInformation el;
  el.handle = 0x123;
  ASSERT_EXPECTED_EL_TO_STRING("id: (null), name: (null), handle: 0x123, runtime_id: (null)");
}

TEST(ElementInformation, ToString_HasRuntimeId)
{
  ElementInformation el;
  el.runtimeId = new int[2];
  el.runtimeId[0] = 123; el.runtimeId[1] = 456;
  el.runtimeIdLength = 2;
  ASSERT_EXPECTED_EL_TO_STRING("id: (null), name: (null), handle: 0x0, runtime_id: [123, 456]");
}

TEST(ElementInformation, ToString_AllTheThings)
{
  ElementInformation el;
  el.name = StringHelper::ToUnmanaged("someName");
  el.id = StringHelper::ToUnmanaged("someId");
  el.handle = 0xffff;
  el.runtimeId = new int[1];
  el.runtimeId[0] = 42789;
  el.runtimeIdLength = 1;
  ASSERT_EXPECTED_EL_TO_STRING("id: someId, name: someName, handle: 0xffff, runtime_id: [42789]");
}

TEST(ElementInformation, ToManagedString)
{
  ElementInformation el;
  el.name = StringHelper::ToUnmanaged("someName");

  auto actual = StringHelper::ToUnmanaged(el.ToManagedString());
  ASSERT_STREQ("id: (null), name: someName, handle: 0x0, runtime_id: (null)", actual);
  delete[] actual;
}
