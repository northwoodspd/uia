#include "stdafx.h"
#include "StringHelper.h"

void StringHelper::CopyToUnmanagedString(String^ source, char* destination, const int destinationSize)
{
	auto unmanagedString = Marshal::StringToHGlobalAnsi(source);
	strncpy_s(destination, destinationSize, (const char*)(void*)unmanagedString,  _TRUNCATE);
	Marshal::FreeHGlobal(unmanagedString);
}

char* StringHelper::ToUnmanaged(String^ source)
{
	const int numberOfBytes = source->Length + 1;
	auto unmanagedString = new char[numberOfBytes];
	CopyToUnmanagedString(source, unmanagedString, numberOfBytes);
	return unmanagedString;
}
