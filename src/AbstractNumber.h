/*
 * AbstractNumber.h
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#ifndef ABSTRACTNUMBER_H_
#define ABSTRACTNUMER_H_
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

class AbstractNumber {
public:
	virtual AbstractNumber * add(AbstractNumber *number) = 0;
	virtual AbstractNumber * multiply(AbstractNumber *number) = 0;
	virtual AbstractNumber * divide(AbstractNumber *number) = 0;
	virtual string toString() = 0;
	virtual double toDouble() = 0;
	virtual AbstractNumber * simplify() = 0;
	virtual string getName() = 0;
	virtual char getSign() = 0;

	AbstractNumber *base, *root, *value;
	vector<AbstractNumber*> nums;

};



#endif /* ABSTRACTNUMBER_H_ */
