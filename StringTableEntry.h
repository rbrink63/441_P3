#pragma once
#include <string>

struct StringTableEntry {
	std::string data;
	StringTableEntry* next = NULL;
};
typedef StringTableEntry* StringTableRef;