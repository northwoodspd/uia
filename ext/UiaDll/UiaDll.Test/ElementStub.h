#include "stdafx.h"

ref class ElementStub : Element
{
public:
  ElementStub(String^ name, ...array<int>^ runtimeIds) : Element()
  {
    _name = name;
    _runtimeIds = runtimeIds;
    _patterns = gcnew array<int>(0);
  }

  virtual property String^ Name
  {
    String^ get() override { return _name; }
    void set(String^ name) { _name = name; }
  }

  virtual property String^ Id
  {
    String^ get() override { return _id; }
    void set(String^ value) override { _id = value; }
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

  virtual property array<int>^ SupportedPatternIds
  {
    array<int>^ get() override { return _patterns; }
  }

  void SetPatterns(... array<int>^ patterns)
  {
    _patterns = patterns;
  }

private:
  String^ _name;
  String^ _id;
  array<int>^ _runtimeIds;
  array<int>^ _patterns;
  int _nativeWindowHandle;
  int _controlTypeId;
};