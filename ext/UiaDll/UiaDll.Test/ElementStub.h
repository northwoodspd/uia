#include "stdafx.h"

ref class ElementStub : Element
{
public:
  ElementStub(String^ name, ...array<int>^ runtimeIds) : Element()
  {
    _name = name;
    _runtimeIds = runtimeIds;
  }

  virtual property String^ Name
  {
    String^ get() override { return _name; }
    void set(String^ name) { _name = name; }
  }

  virtual property array<int>^ RuntimeId
  {
    array<int>^ get() override { return _runtimeIds; }
  }

  virtual property int NativeWindowHandle
  {
    int get() override { return 0; }
  }

  virtual property int ControlTypeId
  {
    int get() override { return 0; }
  }

private:
  String^ _name;
  array<int>^ _runtimeIds;
};