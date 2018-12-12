#pragma once
#include "scanner.h"
#include "token.h"
#include "StringTable.h"
#include "tokStack.h"
#include "constrainer.h"
// #include <stack>

class parser {
public:
	parser();
	void parse(string filename);
private:
	scanner scnr;
	StringTable strTbl;
	tokStack s;		//stack <token> s;
	constrainer cons;
	int  parseError;
	int  chooseProd(token topTok, token inTok);
	void pushRHS(int prodNdx);
	void reportParseError(token topTok, token inTok);
	void checkParseEnd(token topTok, token inTok);
};

const int PERR_NONE = 0;                // no parse error found
const int PERR_NONE_SELECTED = -1;		// Productions found for NT, but none selected
const int PERR_NT_NOT_FOUND = -2;		// No productions found for NT
const int PERR_TERMS_MISMATCH = -3;		// Terminal popped does not match incoming source token
const int PERR_SCANERR = -4;			// Scanner reported an error
const int PERR_UNEX_EOF = -5;			// parse ended with EOF from source but stack not empty
const int PERR_XTRA_TOKS = -6;          // parse ended with more tokens in source but stack empty
const int PERR_CONSTRAINT = -7;         /// constrainer reported an error