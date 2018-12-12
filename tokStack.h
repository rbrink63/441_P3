#pragma once
#include "token.h"

const int STACK_MAX = 1000;
class tokStack {
public:
	tokStack();
	void  push(token t);
	token pop();
	token top();
	void  print();
	bool  empty();
	int   depth();
private:
	token theStack[STACK_MAX];
	int num = 0;
};