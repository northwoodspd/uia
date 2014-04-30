#pragma once
#include "ElementStructures.h"
#include <list>

using namespace System::Collections::Generic;
using namespace std;

ref class ConditionHelper
{
public:
  static Condition^ ConditionFrom(list<SearchConditionPtr>& searchConditions) {
    auto conditions = gcnew List<Condition^>();

    for(auto condition = searchConditions.begin(); condition != searchConditions.end(); ++condition) {
      conditions->Add(ConditionFrom(*condition));
    }

    if(conditions->Count == 1) {
        conditions->Add(Condition::TrueCondition);
    }

    return gcnew AndCondition(conditions->ToArray());
  }

  static Condition^ ConditionFrom(SearchConditionPtr searchCondition) {
    auto automationProperty = AutomationProperty::LookupById(searchCondition->propertyId);
    Object^ value = nullptr;

    if(automationProperty == AutomationElement::ControlTypeProperty) {
      return ControlTypeConditions(searchCondition->numbers, searchCondition->numbersCount);
    } else if(searchCondition->IsString()) {
      value = gcnew String(searchCondition->string);
    } else if(searchCondition->IsPatternAvailableProperty()) {
      value = true;
    } else {
      value = searchCondition->number;
    }

    return gcnew PropertyCondition(automationProperty, value);
  }

private:
  static Condition^ ControlTypeConditions(const int* controlTypeIds, const int controlTypes) {
    if(controlTypes == 1) {
      return ControlType(controlTypeIds[0]);
    }

    auto conditions = gcnew List<Condition^>();
    for(auto index = 0; index < controlTypes; ++index) {
      conditions->Add(ControlType(controlTypeIds[index]));
    }

    return gcnew OrCondition(conditions->ToArray());
  }

  static Condition^ ControlType(const int id) {
    return gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::LookupById(id));
  }
};
