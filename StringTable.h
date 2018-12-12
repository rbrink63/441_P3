#pragma once
#include <string>
#include "StringTableEntry.h"
using namespace std;

const int STRTBL_NUM_BUCKETS = 1000;

// a node in a linked list


class StringTable {
public:
	StringTable();
	~StringTable();
	StringTableRef insert(string item);
	StringTableRef search(string searchName);
	string search(StringTableRef ref);
	void print();
	void destruct();
private:
	StringTableRef bucket[STRTBL_NUM_BUCKETS];
	int hash(string item);
	int hashVal;
	int numCollisions = 0;
	int numEntries = 0;
};

