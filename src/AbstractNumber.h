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
	virtual vector<AbstractNumber*> add(AbstractNumber *number) = 0;
	virtual vector<AbstractNumber*> multiply(AbstractNumber *number) = 0;
	virtual vector<AbstractNumber*> divide(AbstractNumber *number) = 0;
	virtual string toString() = 0;
	virtual double toDouble() = 0;
	virtual bool simplify() = 0;
	virtual string getName() = 0;



};



#endif /* ABSTRACTNUMBER_H_ */
