#include "stdafx.h"
#include "ElementStub.h"
#include <ElementStructures.h>

class ElementStructureTest : public ::testing::Test {
public:
  ElementInformation* ElementWith(String^ name) {
    return new ElementInformation(gcnew ElementStub(name));
  }

  ElementInformation* ElementWith(...array<int>^ runtimeIds) {
    return new ElementInformation(gcnew ElementStub("", runtimeIds));
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

  delete elements;
}
