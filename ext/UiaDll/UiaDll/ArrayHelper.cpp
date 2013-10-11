#include "stdafx.h"
#include "ArrayHelper.h"

array<int>^ ArrayHelper::ToArray(const int items[], const int length) {
  auto managedItems = gcnew array<int>(length);
  for(auto index = 0; index < length; ++index) {
    managedItems[index] = items[index];
  }
  return managedItems;
}


int* ArrayHelper::FromArray(array<int>^ items) {
  auto unmanagedArray = new int[items->Length];

  auto index = 0;
  for each(auto item in items) {
    unmanagedArray[index++] = item;
  }

  return unmanagedArray;
}