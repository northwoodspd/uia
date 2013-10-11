#pragma once
ref class ArrayHelper
{
public:
  static array<int>^ ToArray(const int items[], const int length);
  static int* FromArray(array<int>^ items);
};

