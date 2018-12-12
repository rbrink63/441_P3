#include <iostream>
#include <iomanip>
#include "symbolTbl.h"

//--------------------------------------------------------------
//                           search
//--------------------------------------------------------------
int symbolTbl::search(string symbolName, int scope) {
	int found = -1;
	for (int i = 0; i < numSymbols; i++)
		if (tbl[i].tok.sref->data == symbolName && tbl[i].scope == scope) {
			found = i;
		}
	// remember last symbol searched&found or inserted
	if (found >= 0) lastAccessed = found;
	return found;
} // search()

//--------------------------------------------------------------
//                           insert
//--------------------------------------------------------------

int symbolTbl::insert(token t, int scope) {
	// really need to get rid of this array!!!
	if (numSymbols >= SYMT_MAX_SYMBOLS) {
		cout << "symbolTbl: max symbols exceeded\n";
		return SYMT_MAX_EXCEEDED;
	}

	// something is wrong if token not in String Table
	if (t.sref == NULL) {
		cout << "symbolTbl: given token has no string tbl ref\n";
		return SYMT_NO_SREF;
	}

	// check if identifier with same name and scope already inserted
	if (search(t.sref->data, scope) >= 0) 
		return SYMT_ALREADY_EXISTS;

	// add (append) new symbol to the list
	tbl[numSymbols].tok = t;
	tbl[numSymbols].scope = scope;
	tbl[numSymbols].category = SYMT_UNKNOWN;
	tbl[numSymbols].datatype = SYMT_UNKNOWN;
	lastAccessed = numSymbols; // remember last symbol accessed
	numSymbols++;
	cout << "symbolTbl::insert()\n";
	print();
	return SYMT_INSERTED;
} // insert()

//--------------------------------------------------------------
//                         setUnknownTypes
//--------------------------------------------------------------
void symbolTbl::setUnknownTypes(int dtype) {
	int i = numSymbols - 1;
	while (i >= 0 && tbl[i].datatype == SYMT_UNKNOWN) {
		tbl[i].datatype = dtype;
		i--;
	}
	cout << "symbolTbl::setUnknownTypes()\n";
	print();
} // setUnknownTypes()

//--------------------------------------------------------------
//                         setUnknownCats
//--------------------------------------------------------------
void symbolTbl::setUnknownCats(int categ) {
	int i = numSymbols - 1;
	while (i >= 0 && tbl[i].category == SYMT_UNKNOWN) {
		tbl[i].category = categ;
		i--;
	}
	cout << "symbolTbl::setUnknownCats()\n";
	print();
} // setUnknownCats()

//--------------------------------------------------------------
//                         dropScope
//--------------------------------------------------------------
// NOT USED IN THIS PROJECT
void symbolTbl::dropScope() {
	if (numSymbols <= 0) return;
	int currScope = tbl[numSymbols-1].scope;
	int i = currScope;
	while (numSymbols > 0 && tbl[i].scope == currScope &&
		(tbl[i].category == SYMT_CAT_SIMPLE_VAR ||
	     tbl[i].category == SYMT_CAT_ARRAY))
	{
		numSymbols--;
		i--;
	}
} // dropScope()

//--------------------------------------------------------------
//                        getSym
//--------------------------------------------------------------
symbol symbolTbl::getSym(int ndx) {
	if (ndx >= 0 && ndx < numSymbols)
		return tbl[ndx];
	else {
		cout << "symbolTbl: ndx out of range " << ndx << endl;
		symbol empty;
		empty.tok.tokId = SYMT_EMPTY_SYMBOL;
		return empty;
	}
} // getSym()

//--------------------------------------------------------------
//                        print()
//--------------------------------------------------------------
void symbolTbl::print() {
	token tmp;
	string dt, ctg;
	cout << "========== SYMBOL TABLE (num=" << numSymbols << ") ==================\n";
	cout << "Token ID and name            type           categ   scope\n";
	cout << "--------------------------   ------------   -----   -----\n";
	for (int i = 0; i < numSymbols; i++) {
		if (tbl[i].datatype == SYMT_UNKNOWN)
			dt = "";
		else {
			tmp.tokId = tbl[i].datatype;
			dt = getTokenString(tmp);
		}
		
		cout << left << setw(26) << getTokenString(tbl[i].tok) << "   "
			 << setw(12) << dt << "   " << right
			 << setw(5) << tbl[i].category << "   "
			 << setw(5) << tbl[i].scope << endl;
	}
	getchar();
	cout << endl;
} // print()