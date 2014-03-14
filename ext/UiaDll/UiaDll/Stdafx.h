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
#include <list>

extern "C" Element^ Find(ElementInformationPtr element);