#include <iostream>
#include "parser.h"
#include "grammar.h"

parser::parser() {
	token tok;
	tok.tokId = NT_PROGRAM;  // the PROGRAM non-terminal is the start symbol for Pascal
	s.push(tok);
	parseError = PERR_NONE;
} // constructor

int parser::chooseProd(token topTok, token inTok) { 
	// linear search productions to find first matching non-terminal to LHS 
	bool found = false;
	for (int i = 0; i < GR_NUM_PRODS; i++) {
		if (GR_PROD[i][GR_LHS_NDX] == topTok.tokId) {
			found = true;
			if (GR_PROD[i][GR_SELECT_FNDX] == E) return i; // default production found
			for (int j = GR_SELECT_FNDX; j <= GR_SELECT_LNDX; j++) {
				if (GR_PROD[i][j] == inTok.tokId) return i;
			}
		}
		else if (found) {
			return PERR_NONE_SELECTED;
		}
	}
	return PERR_NT_NOT_FOUND;
} // chooseProd()

void parser::pushRHS(int prodNdx) {
	token t;
	t.tokId = GR_PROD[prodNdx][GR_LHS_NDX];
	for (int i = GR_RHS_LNDX; i >= GR_RHS_FNDX; i--) {
		t.tokId = GR_PROD[prodNdx][i];
		if (t.tokId != E) {
			s.push(t);
		}
	}
} // pushRHS()

void parser::reportParseError(token topTok, token inTok) {
	string err = "Parse Error: ";
	switch (parseError) {
	case PERR_NONE_SELECTED:	err = err + "no production selected for Top Token"; break;
	case PERR_NT_NOT_FOUND:		err = err + "no productions for non-terminal "; break;
	case PERR_TERMS_MISMATCH:	err = err + "input Token found, but Top Token expected"; break;
	case PERR_SCANERR:          err = err + "scan error reported"; break;
	case PERR_UNEX_EOF:         err = err + "unexpected end of source"; break;
	case PERR_XTRA_TOKS:        err = err + "unexpected tokens in source past end of program"; break;
	case PERR_CONSTRAINT:		err = err + "constrainer error\n"; break;
	default:                    err = err + "Unknown code=" + to_string(parseError) + " topTok=" + getTokenString(topTok) + " inTok=" + getTokenString(inTok);
	}
	err += ("\nTopToken=" + getTokenString(topTok) + " InputToken = " + getTokenString(topTok) + "\n");
	cout << err << endl;
} // reportParseError()

void parser::checkParseEnd(token topTok, token inTok) {
	if (parseError == PERR_NONE) {
		if (inTok.tokId == TOK_SCANERR)
			parseError = PERR_SCANERR;
		else if (inTok.tokId == TOK_ENDSRC && !s.empty())
			parseError = PERR_UNEX_EOF;
		else if (inTok.tokId != TOK_ENDSRC && s.empty())
			parseError = PERR_XTRA_TOKS;
	}
	if (parseError == PERR_NONE)
		std::cout << "Parser: success!\n";
	else
		reportParseError(topTok, inTok);
} // checkParseEnd()

void parser::parse(string filename) {
	if (scnr.openSource(filename) == 0) return;
	token inTok = scnr.getNextToken(strTbl), topTok;

	while (inTok.tokId != TOK_SCANERR && inTok.tokId != TOK_ENDSRC && !s.empty() && parseError == PERR_NONE) {
		cout << "\nPARSE: inTok=" << inTok.tokId << " " << getTokenString(inTok) << endl;
		s.print();
		topTok = s.pop();
		if (topTok.tokId < FIRST_NT) 			// if top is terminal
			if (topTok.tokId == inTok.tokId) {	// if top and input match
				if (cons.constrain(inTok)==-1)
					parseError = PERR_CONSTRAINT;
				else
					inTok = scnr.getNextToken(strTbl);
			}
			else 
				parseError = PERR_TERMS_MISMATCH;
		else {  // top is non-Terminal
			int pndx = chooseProd(topTok, inTok); // pndx = PERR_* on not found errors
			if (pndx >= 0) {
				if (cons.constrain(topTok) == -1)
					parseError = PERR_CONSTRAINT;
				else
					pushRHS(pndx);
			}
			else
				parseError = pndx;
		} 
	} // end while loop

	// check if parsing ended well or in error
	checkParseEnd(topTok, inTok);
} // parse()