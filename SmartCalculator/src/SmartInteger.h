/*
 * SmartInteger.h
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#ifndef SmartInteger_H_
#define SmartInteger_H_
#include "MultExpression.h"

using namespace std;

class SmartInteger: public AbstractNumber {
public:
	SmartInteger(const string &input);
	virtual ~SmartInteger();
	vector<AbstractNumber*> add(AbstractNumber *number);
	vector<AbstractNumber*> multiply(AbstractNumber *number);
	vector<AbstractNumber*> divide(AbstractNumber *number);
	string toString();
	double toDouble();
	bool simplify();
	string getName();

private:
	int value;
};


#endif /* SmartInteger_H_ */
