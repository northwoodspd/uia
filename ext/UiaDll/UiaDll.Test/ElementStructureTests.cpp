#include "stdafx.h"
#include <ElementStructures.h>

class ElementStructureTest : public ::testing::Test {
public:
  ElementInformation* ElementWith(String^ name, int runtimeId) {
    auto element = new ElementInformation();
    With(element, name);
    With(element, runtimeId);
    return element;
  }

  ElementInformation* ElementWith(String^ name) {
    return With(new ElementInformation(), name);
  }

  ElementInformation* ElementWith(int runtimeId) {
    return With(new ElementInformation(), runtimeId);
  }

  ElementInformation* With(ElementInformation* element, String^ name) {
    element->name = StringHelper::ToUnmanaged(name);
    return element;
  }

  ElementInformation* With(ElementInformation* element, int runtimeId) {
    auto runtimeIds = gcnew array<int>(1);
    runtimeIds[0] = runtimeId;
    element->runtimeId = ArrayHelper::FromArray(runtimeIds);
    element->runtimeIdLength = 1;
    return element;
  }
};

TEST_F(ElementStructureTest, ItCleansUpTheName)
{
  auto elementInformation = ElementWith("Some Name");
  delete elementInformation;
}

TEST_F(ElementStructureTest, ItCleansUpTheRuntimeId)
{
  auto runtimeId = 123;
  auto elementInformation = ElementWith(runtimeId);
  delete elementInformation;
}

TEST_F(ElementStructureTest, ItCleansUpTheElementsAsWell)
{
  auto elements = new Elements();
  elements->elements = new ElementInformation[2];
  With(&elements->elements[0], "First Element");
  With(&elements->elements[1], "Second Element");
  delete elements;
}
