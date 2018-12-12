#include <iostream>
#include "constrainer.h"

int constrainer::constrain(token t) {
	int rc; // return code from methods

	switch (t.tokId) {
	case NT_PROGRAM: 
		currScope++;			// enter "global" scope
		insertIdents = true;	// insert prog name when ready
		break;
	case NTC_PGM_HEADER:		// parsed the program name
		symTbl.setUnknownCats(NT_PROGRAM); // category of pgm name
		symTbl.setUnknownTypes(TOK_MINUS); // pgm name has no data type
		insertIdents = false;
		break;
	case NTC_SET_LHS: 
		// entering an assignment statement; just consumed LHS Ident
		// TO DO: Get the last symbol accessed from the symbol table:
		//    this will be the variable on the LHS.
		// "Remember" the data type in constType: constType = ...
		constType = symTbl.getSym(symTbl.getLastAccessed()).datatype;

		break;
	case NTC_RHS_END:
		// finished assignment statement
		// TO DO: stop constraining the assignment statement
		insertIdents = false;
		
		break;
	case TOK_IDENT:
		
		int already_in_table;
		// TO DO: 
		// If we are inserting identifiers (parsing declarations)
		// - (try to) insert the token into the symbol table with
		//   the current scope. 
		if (insertIdents){
		    already_in_table = symTbl.insert(t, currScope);
		
		    // - If the insert fails because the ident is already in
		    //   the table, print the following error message:
		    //   "Constrainer: symbol re-declared " << NAME_OF_IDENT << endl;
		    if (already_in_table == SYMT_ALREADY_EXISTS){
		        cout << "Constrainer: symbol re-declared " << getTokenString(t) << endl;
		        //should this be a part of this if?
		        // - If the insert fails for any reason, return -1 (error)
		        return -1;
		    }
		}
		

		// If we are not inserting idents (parsing executable code)
		// - make sure the ident is already declared in this scope.
		else{
		     if (symTbl.search(t.sref->data, currScope) < 0){
			//   If it is not, print the following error and return -1
			// "constrain: identifier undefined: " << NAME_OF_IDENT << endl;
			cout << "constrain: identifier undefined: " << getTokenString(t) << endl; 
		     }
		
		// - If we are doing type checking on an assignment statement
		//   and the type of this ident is not the same as the 
		//   constraining type print the following error message:
		//   "constrain: data type does not match LHS of assignment: " << NAME_OF_IDENT << endl;
		    if (constType > 0 && constType != t.tokId){
			 cout << "constrain: data type does not match LHS of assignment: " << getTokenString(t) << endl;		       	
		    }
		    
		 }

		break;
	case TOK_INT_LIT: case TOK_CHAR_LIT: case TOK_REAL_LIT:
	//Joiner said we may want to break up this one
		// TO DO: 
		// if we are constraining type for an assignment
		// and the token t isn't the same type as the
		// constraint type, print this error message
		// "constrain: data type does not match LHS of assignment: " << LITERAL_VALUE << endl;


		break;
	case TOK_INTEGER: case TOK_REAL: case TOK_STRING:
		// we've received the TYPE of a Declaration Statement
		// TO DO:
		// - set all unknown categories to "simple var" (see constants)
		// - set all unknown types to the token's ID
		// - turn OFF "we are inserting identifiers"

		break;
	case TOK_VAR: 
		// we are at beginning a variable declaration
		// TO DO: turn ON "we are inserting identifiers"
		insertIdents = true;
	
		break;
	} // end switch()
	return 0;
} // constrain()
