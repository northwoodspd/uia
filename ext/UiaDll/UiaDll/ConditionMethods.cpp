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

  #pragma managed(push, off)
  __declspec(dllexport) SearchConditionPtr Condition_Pattern(char* errorInfo, const int errorInfoLength, const int n, const char* arg0, ...) {
    GRAB_VARARGS(patterns, const char*, n);
    return ManagedBuildPatternCondition(patterns, errorInfo, errorInfoLength); 
  }
  #pragma managed(pop)

  #pragma managed(push, off)
  __declspec(dllexport) SearchConditionPtr Condition_ControlType(const int n, const int arg0, ...) {
    GRAB_VARARGS(controlTypes, const int, n);
    return SearchCondition::FromControlTypes(controlTypes);
  }
  #pragma managed(pop)
}