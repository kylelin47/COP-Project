//============================================================================
// Name        : SmartCalculator.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SumExpression.h"
using namespace std;

int main() {
	AbstractNumber * test = new SumExpression("54-7");
	cout << test->toString();


}
