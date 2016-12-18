#pragma once
#include <list>
using namespace std;
using namespace System::Windows::Automation;

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
    for(list<const int>::iterator number = numbers.begin(); number != numbers.end(); ++number, ++index) {
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
    return new SearchCondition(AutomationElement::ControlTypeProperty->Id, controlTypes);
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
