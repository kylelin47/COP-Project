/*
 * MultExpression.h
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#ifndef MultExpression_H_
#define MultExpression_H_
#include "AbstractNumber.h"
#include "SmartInteger.h"
#include <iostream>

using namespace std;

class MultExpression: public AbstractNumber {
public:
	MultExpression(vector<AbstractNumber*> nums);
	virtual ~MultExpression();
	AbstractNumber * add(AbstractNumber *number);
	AbstractNumber * multiply(AbstractNumber *number);
	AbstractNumber * divide(AbstractNumber *number);
	string toString();
	void split(vector<AbstractNumber*> &num, vector<AbstractNumber*> &den, const string &text, char sep1, char sep2);
	vector<string> expression;
	vector<AbstractNumber*> numerator;
	vector<AbstractNumber*> denominator;
	char getSign();
	double toDouble();
	AbstractNumber* simplify();
	string getName();
	int getTypeFromString(string input);
	int count(string input, int begin, int end, char symbol);

	vector <AbstractNumber*> nums;

private:
	char sign;
};


#endif /* MultExpression_H_ */
