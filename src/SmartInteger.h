/*
 * SmartInteger.h
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#ifndef SmartInteger_H_
#define SmartInteger_H_
#include "SumExpression.h"

using namespace std;

class SmartInteger: public AbstractNumber {
public:
	SmartInteger(int value);
    SmartInteger(const string &input);
	virtual ~SmartInteger();
	AbstractNumber * add(AbstractNumber *number);
	AbstractNumber * multiply(AbstractNumber *number);
	AbstractNumber * divide(AbstractNumber *number);
	string toString();
	double toDouble();
	AbstractNumber * simplify();
	string getName();

private:
	int value;
};


#endif /* SmartInteger_H_ */
