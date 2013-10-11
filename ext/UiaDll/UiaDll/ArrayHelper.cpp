#include "stdafx.h"
#include "ArrayHelper.h"

array<int>^ ArrayHelper::ToArray(const int items[], const int length) {
  auto managedItems = gcnew array<int>(length);
  for(auto index = 0; index < length; ++index) {
    managedItems[index] = items[index];
  }
  return managedItems;
}