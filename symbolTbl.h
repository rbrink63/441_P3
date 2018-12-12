#pragma once
#include <string>
#include "token.h"
using namespace std;

struct symbol {
	token tok;		// should have a ref into string table
	int scope;		// scope level. global/main=1, proc/fun=2
	int datatype;   // TOK_CHAR, TOK_FLOAT or TOK_REAL
	int category;	// variable, program name, func name, etc.
	int arr_start;  // array start index
	int arr_last;   // array end index
	// TODO: implement records, with a list of members/types
};

const int SYMT_MAX_SYMBOLS = 200;

struct symbolTbl {
public:
	int insert(token t, int scope);
	int search(string symbolName, int scope);
	int getLastAccessed() { return lastAccessed;  }
	void setUnknownTypes(int dtype);
	void setUnknownCats(int categ);
	symbol getSym(int ndx);
	void dropScope();
	void print();
private:
	// we could do better than this, but its quick
	symbol tbl[SYMT_MAX_SYMBOLS];
	int numSymbols = 0;
	int lastAccessed = -1; //index of symbol last accessed
};

// insert() return codes
const int SYMT_NO_SREF = -2;
const int SYMT_MAX_EXCEEDED = -1;
const int SYMT_INSERTED = 0;
const int SYMT_ALREADY_EXISTS = 1;

const int SYMT_UNKNOWN = -999;        // symbol.* not yet known
const int SYMT_EMPTY_SYMBOL = -9999;

// categories for symbol.category
const int SYMT_CAT_PGM_NAME = 1;
const int SYMT_CAT_PROC_NAME = 2;
const int SYMT_CAT_SIMPLE_VAR = 3;
const int SYMT_CAT_ARRAY = 4;

