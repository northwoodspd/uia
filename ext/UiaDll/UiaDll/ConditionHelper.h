#pragma once
#include "SearchCondition.h"
#include <list>
#include <functional>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Automation;
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
      return Or(searchCondition->numbers, searchCondition->numbersCount, ControlType);
    } else if(searchCondition->IsString()) {
      value = gcnew String(searchCondition->string);
    } else if(searchCondition->IsPattern()) {
      return Or(searchCondition->patterns, searchCondition->patternsCount, Pattern);
    } else {
      value = searchCondition->number;
    }

    return gcnew PropertyCondition(automationProperty, value);
  }

private:
  static Condition^ Or(const int* ids, const int count, std::function<Condition^(int)> conditionFor) {
    if( count == 1 ) {
      return conditionFor(ids[0]);
    }

    auto conditions = gcnew List<Condition^>();
    for(auto index = 0; index < count; ++index) {
      conditions->Add(conditionFor(ids[index]));
    }

    return gcnew OrCondition(conditions->ToArray());
  }

  static Condition^ ControlType(const int id) {
    return gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::LookupById(id));
  }

  static Condition^ Pattern(const int patternId) {
    return gcnew PropertyCondition(AutomationProperty::LookupById(patternId), true);
  }
};
