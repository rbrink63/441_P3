all: constrainer 

constrainer: main.cpp parser.cpp parser.h constrainer.h constrainer.cpp StringTable.cpp main.cpp symbolTbl.cpp symbolTbl.h scanner.cpp tokStack.cpp token.cpp StringTable.h StringTableEntry.h grammar.h scanner.h tokStack.h token.h 
	g++ -o compile.out -std=c++11 parser.cpp StringTable.cpp main.cpp scanner.cpp token.cpp SymbolTbl.cpp constrainer.cpp tokStack.cpp

.PHONY: clean

clean:
	rm -f compile.out
