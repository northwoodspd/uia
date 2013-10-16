#include "stdafx.h"
#include "ElementStub.h"
#include <ElementStructures.h>

class ElementsTest : public ::testing::Test {
public:
  array<Element^>^ ElementsWithNames(...array<String^>^ names) {
    auto elements = gcnew array<Element^>(names->Length);
    auto index = 0;
    for each(auto name in names) {
      elements[index++] = gcnew ElementStub(name);
    }
    return elements;
  }
};

TEST_F(ElementsTest, ItCanBeInitialized)
{
  auto elements = Elements(ElementsWithNames("First", "Second"));
  ASSERT_STREQ("First", elements.elements[0].name);
  ASSERT_STREQ("Second", elements.elements[1].name);
}
