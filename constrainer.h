#pragma once
#include "token.h"
#include "symbolTbl.h"
using namespace std;

class constrainer {
public:
	int constrain(token t);
private:
	symbolTbl symTbl;
	int currScope = 0;				// increments as scope deepens
	bool insertIdents = false;		// insert identifiers?
	int  constType = 0;				// 0 = not currently constraining data types
	                                // TOK_INTEGER/REAL/CHAR = constrain types on lits and idents
};

const int WO_PGM_HEADER = 1;
