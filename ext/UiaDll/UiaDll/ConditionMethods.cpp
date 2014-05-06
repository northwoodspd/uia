#include "Stdafx.h"

using namespace std;

extern "C" {
  __declspec(dllexport) void Condition_Release(SearchConditionPtr searchCondition) {
    delete searchCondition;
  }

  _declspec(dllexport) SearchConditionPtr Condition_Id(const char* id) {
    return new SearchCondition(AutomationElement::AutomationIdProperty->Id, id);
  }

  _declspec(dllexport) SearchConditionPtr Condition_Name(const char* name) {
    return new SearchCondition(AutomationElement::NameProperty->Id, name);
  }

   SearchConditionPtr ManagedBuildPatternCondition(list<const char*>& patterns, char* errorInfo, const int errorInfoLength) {
    try {
      list<const int> patternIds;

      for(auto pattern = patterns.begin(); pattern != patterns.end(); ++pattern) {
        patternIds.push_back(PropertyExtensions::PropertyId(gcnew String(*pattern)));
      }

      return new SearchCondition(patternIds);
    } catch(Exception^ e) {
      StringHelper::CopyToUnmanagedString(e->Message, errorInfo, errorInfoLength);
      return NULL;
    }
  }

  __declspec(dllexport) SearchConditionPtr Condition_Pattern(char* errorInfo, const int errorInfoLength, const int n, const char* arg0, ...) {
    va_list arguments;
    va_start(arguments, arg0);

    list<const char*> patterns;
    patterns.push_back(arg0);
    for(auto index = 1; index < n; ++index) {
      auto value = va_arg(arguments, const char*);
      patterns.push_back(value);
    }

    return ManagedBuildPatternCondition(patterns, errorInfo, errorInfoLength); 
  }

  __declspec(dllexport) SearchConditionPtr Condition_ControlType(const int n, const int arg0, ...) {
    va_list arguments;
    va_start(arguments, arg0);

    list<const int> controlTypes;
    controlTypes.push_back(arg0);
    for(auto index = 1; index < n; index++) {
      auto value = va_arg(arguments, int);
      controlTypes.push_back(value);
    }

    return SearchCondition::FromControlTypes(controlTypes);
  }
}