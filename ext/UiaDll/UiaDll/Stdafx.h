// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <Windows.h>

using namespace System;
using namespace UIA::Helper;

#include "StringHelper.h"
#include "ArrayHelper.h"
#include "ElementStructures.h"
#include "PatternInformationStructures.h"
#include "SearchCondition.h"
#include <list>

extern "C" Element^ ElementFrom(ElementInformationPtr element);

#define GRAB_VARARGS(argument_list, arg_type, arg_count) \
  va_list arguments;\
  va_start(arguments, arg0);\
  list<##arg_type##> ##argument_list##;\
  ##argument_list##.push_back(arg0);\
  for(auto index = 1; index < ##arg_count##; ++index) {\
    auto value = va_arg(arguments, ##arg_type##);\
    ##argument_list##.push_back(value);\
  }