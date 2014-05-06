#pragma once
#include "ArrayHelper.h"
#include "StringHelper.h"

#include <list>
using namespace std;

typedef struct _SearchCondition {
  int propertyId;

  int number;
  char* string;
  int* numbers;
  int numbersCount;
  int* patterns;
  int patternsCount;

  _SearchCondition(const int id) : string(NULL), numbers(NULL), patterns(NULL) {
    Reset(id);
  }

  _SearchCondition(const int id, const char* s) : string(NULL), numbers(NULL), patterns(NULL) {
    Reset(id);

    auto length = strnlen_s(s, 10000);
    auto size = length + 1;
    this->string = new char[size];
    strcpy_s(this->string, size, s);
  }

  _SearchCondition(const int id, const int number) : string(NULL), numbers(NULL), patterns(NULL) {
    Reset(id);
    this->number = number;
  }

  _SearchCondition(const int id, list<const int>& numbers) : string(NULL), numbers(NULL), patterns(NULL) {
    Reset(id);
    numbersCount = numbers.size();
    this->numbers = new int[numbersCount];

    int index = 0; 
    for(std::list<const int>::iterator number = numbers.begin(); number != numbers.end(); ++number, ++index) {
      this->numbers[index] = *number;
    }
  }

  _SearchCondition(list<const int>& patterns) : string(NULL), numbers(NULL), patterns(NULL) {
    Reset(patterns.front());

    patternsCount = patterns.size();
    this->patterns = new int[patternsCount];

    int index = 0;
    for(std::list<const int>::iterator pattern = patterns.begin(); pattern != patterns.end(); ++pattern, ++index) {
      this->patterns[index] = * pattern;
    }
  }

  bool HasNumbers() {
    return NULL != numbers;
  }

  bool IsString() {
    return NULL != string;
  }

  bool IsPattern() {
    return NULL != patterns;
  }

  static _SearchCondition* FromControlTypes(list<const int>& controlTypes) {
    return new SearchCondition(System::Windows::Automation::AutomationElement::ControlTypeProperty->Id, controlTypes);
  }

  void Reset(const int id) {
    propertyId = id;
    delete[] string; delete[] numbers; delete[] patterns;
    string = NULL; numbers = NULL;
    number = 0; numbersCount = 0; patternsCount = 0;
  }

  ~_SearchCondition() {
    Reset(propertyId);
  }

} SearchCondition, *SearchConditionPtr;

typedef struct _ElementInformation {
  int nativeWindowHandle;
  int* runtimeId;
  int runtimeIdLength;
  char* name;
  char* className;
  int controlTypeId;
  int* patterns;
  int patternsLength;
  char* id;

  bool isEnabled;
  bool isVisible;
  bool hasKeyboardFocus;
  long boundingRectangle[4];

  _ElementInformation() : name(NULL), nativeWindowHandle(0), runtimeId(NULL), patterns(NULL), id(NULL), className(NULL) {}

  _ElementInformation(Element^ element) : name(NULL), nativeWindowHandle(0), runtimeId(NULL), patterns(NULL), id(NULL), className(NULL) {
    Refresh(element);
  }

  static _ElementInformation* From(Element^ element) {
    return nullptr != element ? new _ElementInformation(element) : NULL;
  }

  static _ElementInformation* From(...array<Element^>^ elements) {
    if( nullptr == elements || elements->Length == 0 ) return NULL;

    auto elementInformation = new _ElementInformation[elements->Length];
    auto index = 0;
    for each(auto element in elements) {
      elementInformation[index++].Refresh(element);
    }

    return elementInformation;
  }

  void Refresh(Element^ element) {
    Reset();
    id = StringHelper::ToUnmanaged(element->Id);
    name = StringHelper::ToUnmanaged(element->Name);
    className = StringHelper::ToUnmanaged(element->ClassName);
    nativeWindowHandle = element->NativeWindowHandle;
    runtimeId = ArrayHelper::FromArray(element->RuntimeId);
    runtimeIdLength = element->RuntimeId->Length;
    controlTypeId = element->ControlTypeId;
    patterns = ArrayHelper::FromArray(element->SupportedPatternIds);
    patternsLength = element->SupportedPatternIds->Length;

    isEnabled = element->IsEnabled;
    isVisible = element->IsVisible;
    hasKeyboardFocus = element->HasKeyboardFocus;

    auto r = element->BoundingRectangle;
    for(auto coord = 0; coord < 4; coord++) {
      boundingRectangle[coord] = r[coord];
    }
  }

  ~_ElementInformation() {
    Reset();
  }

private:
  void Reset() {
    delete[] name; delete[] runtimeId; delete[] patterns; delete[] id; delete[] className;
    name = NULL; runtimeId = NULL; patterns = NULL; id = NULL; className = NULL;
  }

} ElementInformation, *ElementInformationPtr;
