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
    int get() override { return _nativeWindowHandle; }
    void set(int value) { _nativeWindowHandle = value; }
  }

  virtual property int ControlTypeId
  {
    int get() override { return _controlTypeId; }
    void set(int value) override { _controlTypeId = value; }
  }

private:
  String^ _name;
  array<int>^ _runtimeIds;
  int _nativeWindowHandle;
  int _controlTypeId;
};