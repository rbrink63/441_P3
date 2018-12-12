#pragma once
#include "token.h"
// Grammar Assumptions:
// 1. All productions for a given non-terminal (NT) are listed in consecutive rows
// 2. When the first element of the selection set is empty (E), the production is
//    the "default" production for the NT.
// 3. If there is a default production for a NT, it will be listed last.

// Grammar Table dimensions and index constants
const int GR_NUM_PRODS = 83;	// number of productions (rows) in the grammar
const int GR_NUM_COLS = 12;		// total number of columns in the grammar table
const int GR_LHS_NDX = 0;		// index of the Left Hand Side of the production (Non-Terminal Token)
const int GR_RHS_FNDX = 1;		// first index of the Right Hand Side of the production 
const int GR_RHS_LNDX = 8;		// last  index of the Right Hand Side of the production
const int GR_SELECT_FNDX = 9;	// first index of the Select1 Set
const int GR_SELECT_LNDX = 11;  // last  index of the Select1 Set

// The Pascal Grammar Productions and Select Sets
const int GR_PROD[GR_NUM_PRODS][GR_NUM_COLS] = {
	{ NT_PROGRAM,TOK_PROGRAM, TOK_IDENT, NTC_PGM_HEADER, TOK_SEMIC, NT_DECLARATIONS, NT_SUBPGM_DCLS, NT_CMPD_STMT, TOK_PERIOD, TOK_PROGRAM, E, E },
	{ NTC_PGM_HEADER, E,E,E,E,E,E,E,E,E,E,E},
	{ NT_ID_LIST,TOK_IDENT, NT_ID_LIST_END, E, E, E, E, E, E, TOK_IDENT, E, E },
	{ NT_ID_LIST_END,TOK_COMMA, NT_ID_LIST, E, E, E, E, E, E, TOK_COMMA, E, E },
	{ NT_ID_LIST_END,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_DECLARATIONS,TOK_VAR, NT_ID_LIST, TOK_COLON, NT_TYPE, TOK_SEMIC, NT_DECLARATIONS, E, E, TOK_VAR, E, E },
	{ NT_DECLARATIONS,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_TYPE,TOK_ARRAY, TOK_LBRKT, TOK_INT_LIT, TOK_DOTDOT, TOK_INT_LIT, TOK_RBRKT, TOK_OF, NT_STD_TYPE, TOK_ARRAY, E, E },
	{ NT_TYPE,NT_STD_TYPE, E, E, E, E, E, E, E, E, E, E },
	{ NT_STD_TYPE,TOK_INTEGER, E, E, E, E, E, E, E, TOK_INTEGER, E, E },
	{ NT_STD_TYPE,TOK_REAL, E, E, E, E, E, E, E, TOK_REAL, E, E },
	{ NT_STD_TYPE,TOK_STRING, E, E, E, E, E, E, E, TOK_STRING, E, E },
	{ NT_SUBPGM_DCLS,NT_SUBPGM_DCL, TOK_SEMIC, NT_SUBPGM_DCLS, E, E, E, E, E, TOK_FUNCTION, TOK_PROCEDURE, E },
	{ NT_SUBPGM_DCLS,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_SUBPGM_DCL,NT_SUBPGM_HEAD, NT_DECLARATIONS, NT_CMPD_STMT, E, E, E, E, E, TOK_FUNCTION, TOK_PROCEDURE, E },
	{ NT_SUBPGM_HEAD,TOK_FUNCTION, TOK_IDENT, NT_ARGS, TOK_COLON, NT_STD_TYPE, TOK_SEMIC, E, E, TOK_FUNCTION, E, E },
	{ NT_SUBPGM_HEAD,TOK_PROCEDURE, TOK_IDENT, NT_ARGS, TOK_SEMIC, E, E, E, E, TOK_PROCEDURE, E, E },
	{ NT_ARGS,TOK_LEFTPAR, NT_PARM_LIST, TOK_RIGHTPAR, E, E, E, E, E, TOK_LEFTPAR, E, E },
	{ NT_ARGS,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_PARM_LIST,NT_ID_LIST, TOK_COLON, NT_TYPE, NT_PARM_LIST_END, E, E, E, E, E, E, E },
	{ NT_PARM_LIST_END,TOK_SEMIC, NT_PARM_LIST, E, E, E, E, E, E, TOK_SEMIC, E, E },
	{ NT_PARM_LIST_END,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_CMPD_STMT,TOK_BEGIN, NT_OPT_STMTS, TOK_END, E, E, E, E, E, E, E, E },
	{ NT_OPT_STMTS,E, E, E, E, E, E, E, E, TOK_END, E, E },
	{ NT_OPT_STMTS,NT_STMT_LIST, E, E, E, E, E, E, E, E, E, E },
	{ NT_STMT_LIST,NT_STMT, NT_STMT_LIST_END, E, E, E, E, E, E, E, E, E },
	{ NT_STMT_LIST_END,TOK_SEMIC, NT_STMT_LIST, E, E, E, E, E, E, TOK_SEMIC, E, E },
	{ NT_STMT_LIST_END,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_STMT,TOK_IDENT, NT_PROC_OR_ASSIGN, E, E, E, E, E, E, TOK_IDENT, E, E },
	{ NT_STMT,NT_CMPD_STMT, E, E, E, E, E, E, E, TOK_BEGIN, E, E },
	{ NT_STMT,TOK_IF, NT_EXPR, TOK_THEN, NT_STMT, TOK_ELSE, NT_STMT, E, E, TOK_IF, E, E },
	{ NT_STMT,TOK_WHILE, NT_EXPR, TOK_DO, NT_STMT, E, E, E, E, TOK_WHILE, E, E },
	{ NT_STMT,TOK_FOR, NT_VARIABLE, TOK_ASSIGN, NT_EXPR, NT_END_FOR, E, E, E, TOK_FOR, E, E },
	{ NT_STMT,TOK_WRITELN,TOK_LEFTPAR,NT_WRITEABLE,TOK_RIGHTPAR,E,E,E,E,TOK_WRITELN,E,E },
	{ NT_WRITEABLE, NT_VARIABLE, E,E,E,E,E,E,E, TOK_IDENT,E,E},
	{ NT_WRITEABLE, TOK_INT_LIT, E,E,E,E,E,E,E, TOK_INT_LIT,E,E },
	{ NT_WRITEABLE, TOK_CHAR_LIT, E,E,E,E,E,E,E, TOK_CHAR_LIT, E,E},
	{ NT_WRITEABLE, TOK_REAL_LIT, E,E,E,E,E,E,E, TOK_REAL_LIT, E,E },
	{ NT_PROC_OR_ASSIGN,NT_PROC_STMT_END, E, E, E, E, E, E, E, TOK_LEFTPAR, TOK_SEMIC, E },
	{ NT_PROC_OR_ASSIGN,NT_VAR_END,NTC_SET_LHS,  TOK_ASSIGN, NT_EXPR, NTC_RHS_END, E, E, E, E, E, E },
	{ NTC_SET_LHS, E,E,E,E,E,E,E,E, E,E,E},
	{ NTC_RHS_END, E,E,E,E,E,E,E,E, E,E,E },
	{ NT_END_FOR,TOK_TO, NT_EXPR, TOK_DO, E, E, E, E, E, TOK_TO, E, E },
	{ NT_END_FOR,TOK_DOWNTO, NT_EXPR, TOK_DO, E, E, E, E, E, TOK_DOWNTO, E, E },
	{ NT_VARIABLE,TOK_IDENT, NT_VAR_END, E, E, E, E, E, E, E, E, E },
	{ NT_VAR_END,TOK_LBRKT, NT_EXPR, TOK_RBRKT, E, E, E, E, E, TOK_LBRKT, E, E },
	{ NT_VAR_END,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_PROC_STMT_END,TOK_LEFTPAR, NT_EXPR_LIST, TOK_RIGHTPAR, E, E, E, E, E, TOK_LEFTPAR, E, E },
	{ NT_PROC_STMT_END,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_EXPR_LIST,NT_EXPR, NT_EXPR_LIST_END, E, E, E, E, E, E, E, E, E },
	{ NT_EXPR_LIST_END,TOK_COMMA, NT_EXPR_LIST, E, E, E, E, E, E, TOK_COMMA, E, E },
	{ NT_EXPR_LIST_END,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_EXPR,NT_SIMPLE_EXPR, NT_EXPR_END, E, E, E, E, E, E, E, E, E },
	{ NT_EXPR_END,NT_RELOP, NT_SIMPLE_EXPR, E, E, E, E, E, E, TOK_LTHAN, TOK_LT_EQ, TOK_EQUAL },
	{ NT_EXPR_END,NT_RELOP, NT_SIMPLE_EXPR, E, E, E, E, E, E, TOK_GTHAN, TOK_GT_EQ, TOK_NOT_EQ },
	{ NT_EXPR_END,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_RELOP,TOK_LTHAN, E, E, E, E, E, E, E, TOK_LTHAN, E, E },
	{ NT_RELOP,TOK_LT_EQ, E, E, E, E, E, E, E, TOK_LT_EQ, E, E },
	{ NT_RELOP,TOK_GTHAN, E, E, E, E, E, E, E, TOK_GTHAN, E, E },
	{ NT_RELOP,TOK_GT_EQ, E, E, E, E, E, E, E, TOK_GT_EQ, E, E },
	{ NT_RELOP,TOK_NOT_EQ, E, E, E, E, E, E, E, TOK_NOT_EQ, E, E },
	{ NT_RELOP,TOK_EQUAL, E, E, E, E, E, E, E, TOK_EQUAL, E, E },
	{ NT_SIMPLE_EXPR,NT_SIGN, NT_TERM, NT_SIMPLE_EXPR_END, E, E, E, E, E, TOK_PLUS, TOK_MINUS, E },
	{ NT_SIMPLE_EXPR,NT_TERM, NT_SIMPLE_EXPR_END, E, E, E, E, E, E, E, E, E },
	{ NT_SIMPLE_EXPR_END,NT_ADD_OP, NT_SIMPLE_EXPR, E, E, E, E, E, E, TOK_PLUS, TOK_MINUS, E },
	{ NT_SIMPLE_EXPR_END,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_ADD_OP,TOK_PLUS, E, E, E, E, E, E, E, TOK_PLUS, E, E },
	{ NT_ADD_OP,TOK_MINUS, E, E, E, E, E, E, E, TOK_MINUS, E, E },
	{ NT_TERM,NT_FACTOR, NT_TERM_END, E, E, E, E, E, E, E, E, E },
	{ NT_TERM_END,NT_MUL_OP, NT_TERM, E, E, E, E, E, E, TOK_STAR, TOK_SLASH, E },
	{ NT_TERM_END,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_MUL_OP,TOK_SLASH, E, E, E, E, E, E, E, TOK_SLASH, E, E },
	{ NT_MUL_OP,TOK_STAR, E, E, E, E, E, E, E, TOK_STAR, E, E },
	{ NT_FACTOR,TOK_IDENT, NT_FACTOR_END, E, E, E, E, E, E, TOK_IDENT, E, E },
	{ NT_FACTOR,TOK_INT_LIT, E, E, E, E, E, E, E, TOK_INT_LIT, E, E },
	{ NT_FACTOR,TOK_REAL_LIT, E, E, E, E, E, E, E, TOK_REAL_LIT, E, E },
	{ NT_FACTOR,TOK_CHAR_LIT, E, E, E, E, E, E, E, TOK_CHAR_LIT, E, E },
	{ NT_FACTOR,TOK_LEFTPAR, NT_EXPR, TOK_RIGHTPAR, E, E, E, E, E, TOK_LEFTPAR, E, E },
	{ NT_FACTOR,TOK_NOT, NT_FACTOR, E, E, E, E, E, E, TOK_NOT, E, E },
	{ NT_FACTOR_END,TOK_LEFTPAR, NT_EXPR_LIST, TOK_RIGHTPAR, E, E, E, E, E, TOK_LEFTPAR, E, E },
	{ NT_FACTOR_END,E, E, E, E, E, E, E, E, E, E, E },
	{ NT_SIGN,TOK_PLUS, E, E, E, E, E, E, E, TOK_PLUS, E, E },
	{ NT_SIGN,TOK_MINUS, E, E, E, E, E, E, E, TOK_MINUS, E, E }
};
