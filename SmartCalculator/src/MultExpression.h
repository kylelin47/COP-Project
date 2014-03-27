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
	MultExpression(const string &input);
	virtual ~MultExpression();
	vector<AbstractNumber*> add(AbstractNumber *number);
	vector<AbstractNumber*> multiply(AbstractNumber *number);
	vector<AbstractNumber*> divide(AbstractNumber *number);
	string toString();
	void split(vector<AbstractNumber*> &num, vector<AbstractNumber*> &den, const string &text, char sep1, char sep2);
	vector<string> expression;
	vector<AbstractNumber*> numerator;
	vector<AbstractNumber*> denominator;
	char getSign();
	double toDouble();
	bool simplify();
	string getName();
	int getTypeFromString(string input);

private:
	char sign;
};


#endif /* MultExpression_H_ */
