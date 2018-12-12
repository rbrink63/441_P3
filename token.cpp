#include <iostream>
#include "token.h"

//------------------------------------------------------------------------------------
//                            constructor and short methods
//------------------------------------------------------------------------------------
// Given a token, prints its token string
//------------------------------------------------------------------------------------
void printToken(token tok) { std::cout << getTokenString(tok); }

//------------------------------------------------------------------------------------
//                                     getTokenString()
//------------------------------------------------------------------------------------
// Given a token, returns a string equivalent of the int Token ID. When the token is
// an Identifier or Literal, also prints its String Table value.
//------------------------------------------------------------------------------------
std::string getTokenString(token tok) {
	int id = tok.tokId;
	std::string s;

	if (id >= 0 && id <= NUM_RES_WORDS)
		s = RES_WORDS[id];
	else if (id < 0 && id > -NUM_OTHER_TOKIDS) {
		s = OTHER_TOKIDS[-id];
		if (id <= TOK_IDENT) {	// a literal: print its value from the string table
			if (tok.sref)
				s = s + "=[" + tok.sref->data + "]";
			else
				s = s + "=[]";
		}
	}
	else if (id >= FIRST_NT && id <= LAST_NT)
		s = NON_TERMINAL[id - FIRST_NT];
	else
		s =  "INVALID_TOK_ID=" + id;
	return s;
} // getTokenString()