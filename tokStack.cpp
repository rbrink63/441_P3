#include <iostream>
#include <iomanip>
#include "tokStack.h"

//-----------------------------------------------------------------------------------------
//                                constructor and getters
//-----------------------------------------------------------------------------------------
tokStack::tokStack()   { num = 0; }
int  tokStack::depth() { return num; }
bool tokStack::empty() { return (num == 0); }

//-----------------------------------------------------------------------------------------
//                                        push()
//-----------------------------------------------------------------------------------------
void tokStack::push(token t) {
	if (num < STACK_MAX)
		theStack[num++] = t;
	else
		std::cout << "Stack overflow\n";
}

//-----------------------------------------------------------------------------------------
//                                        pop()
//-----------------------------------------------------------------------------------------
token tokStack::pop() {
	token t;
	if (num > 0)
		t = theStack[--num];
	else 
		std::cout << "Stack underflow\n";
	return t;
}

//-----------------------------------------------------------------------------------------
//                                        top()
//-----------------------------------------------------------------------------------------
token tokStack::top() { 
	token t;  
	if (num > 0) 
		t = theStack[num - 1]; 
	return t; 
}

//-----------------------------------------------------------------------------------------
//                                        print()
//-----------------------------------------------------------------------------------------
void tokStack::print() {
	static bool run = false; 
	std::cout << "Stack print: n=" << num << std::endl;
	for (int i = num - 1; i >= 0; i--)
		std::cout << std::setw(3) << theStack[i].tokId << " " << getTokenString(theStack[i]) << std::endl;
//	if (!run)
//		if (getchar() == 'r') run = true;
}
