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

  virtual property String^ HelpText
  {
    String^ get() override { return _helpText; }
    void set(String^ helpText) { _helpText = helpText; }
  }

  virtual property String^ ClassName
  {
    String^ get() override { return _className; }
    void set(String^ className) { _className = className; }
  }

  virtual property String^ Id
  {
    String^ get() override { return _id; }
    void set(String^ value) { _id = value; }
  }

  virtual property bool IsEnabled
  {
    bool get() override { return _isEnabled; }
    void set(bool value) { _isEnabled = value; }
  }

  virtual property bool IsVisible
  {
    bool get() override { return _isVisible; }
    void set(bool value) { _isVisible = value; }
  }

  virtual property bool HasKeyboardFocus
  {
    bool get() override { return _hasKeyboardFocus; }
    void set(bool value) { _hasKeyboardFocus = value; }
  }

  virtual property array<int>^ RuntimeId
  {
    array<int>^ get() override { return _runtimeIds; }
  }

  virtual property array<int>^ BoundingRectangle
  {
    array<int>^ get() override {
      if( _throwOnBoundingRectangle ) {
        throw gcnew System::Windows::Automation::ElementNotAvailableException("oops");
      }
      return gcnew array<int> {0, 0, 0, 0};
    }
  }

  void SetupBoundingRectangleToThrow() {
    _throwOnBoundingRectangle = true;
  }

  virtual property int NativeWindowHandle
  {
    int get() override { return _handle; }
    void set(int value) { _handle = value; }
  }

  virtual property int ControlTypeId
  {
    int get() override { return _controlTypeId; }
    void set(int value) { _controlTypeId = value; }
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
  String^ _helpText;
  String^ _className;
  String^ _id;
  array<int>^ _runtimeIds;
  array<int>^ _patterns;
  int _handle;
  int _controlTypeId;
  bool _isEnabled;
  bool _isVisible;
  bool _hasKeyboardFocus;
  bool _throwOnBoundingRectangle;
};