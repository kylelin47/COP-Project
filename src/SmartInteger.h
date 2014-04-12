/*
 * SmartInteger.h
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#ifndef SmartInteger_H_
#define SmartInteger_H_
#include "AbstractNumber.h"

using namespace std;

class SmartInteger: public AbstractNumber {
public:
	SmartInteger(int value);
	SmartInteger(int value, char sign);
    SmartInteger(const string &input);
	virtual ~SmartInteger();
	tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>number);
	string toString();
	double toDouble();
	tr1::shared_ptr<AbstractNumber> simplify();
	string getName();
	char getSign();
	tr1::shared_ptr<AbstractNumber> getValue(string name);
	tr1::shared_ptr<AbstractNumber> noSign();
	int GCF(int x, int y);


private:
	char sign;
	int value;
};


#endif /* SmartInteger_H_ */
