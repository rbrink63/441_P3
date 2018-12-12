#include <iostream>
#include <iomanip>
#include "StringTable.h"

StringTable::StringTable() {
	for (int i = 0; i < STRTBL_NUM_BUCKETS; i++)
		bucket[i] = NULL;
} // constructor

void StringTable::destruct() {
	for (int i = 0; i < STRTBL_NUM_BUCKETS; i++) {
		if (bucket[i]) {
			StringTableRef q, p = bucket[i];
			while (p) {
				q = p;
				p = p->next;
				delete q;
			}
			bucket[i] = NULL;
		}
	}
} // destruct 
StringTable::~StringTable() { destruct(); }

StringTableRef StringTable::insert(string item) {
	StringTableRef p = search(item);
	if (p) return p;
	p = new StringTableEntry;
	p->data = item;
	p->next = bucket[hashVal];
	numEntries++;
	if (bucket[hashVal]) numCollisions++;
	bucket[hashVal] = p;
	return p;
} // insert()

StringTableRef StringTable::search(string searchName) {
	if (searchName == "") return NULL;
	int hv = hash(searchName);
	StringTableRef p = bucket[hv];
	while (p) {
		if (p->data == searchName)
			return p;
		p = p->next;
	}
	return NULL;
} // search(string searchName)

string StringTable::search(StringTableRef ref) {
	if (ref == NULL) return "";
	return ref->data;
} // search(StringTableRef)

void StringTable::print() {
	cout << "STRING TABLE :\n";
	for (int i = 0; i < STRTBL_NUM_BUCKETS; i++) {
		if (bucket[i]) {
			cout << "[" << setw(4) << i << "]:  " << bucket[i]->data << endl;
			StringTableRef p = bucket[i]->next;
			while (p) {
				cout << "         " << p->data << endl;
				p = p->next;
			}
		}
	}
	cout << "Collision Percentage: " << (100.0 * numCollisions) / numEntries << endl;
} // print()

int StringTable::hash(string item) {
	int sum = 0, len = item.length();
	for (int i = 0; i < len; i++)
		sum += item[i];
	hashVal = sum % STRTBL_NUM_BUCKETS;
	return hashVal;
} // hash()