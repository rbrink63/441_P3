#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#include "token.h"
#include "parser.h"

int main(int argc, char* argv[]) {
	/*
	for (int i = 0; i < 39; i++)
		cout << setw(3) << i << " " << NON_TERMINAL[i] << endl;
	system("pause");
	*/
	parser p;
	if (argc < 2)
		cout << "No file name given on command line\n";
	else {
		string fn = argv[1];
		p.parse(fn);
	}
	system("pause");
	return 0;
}