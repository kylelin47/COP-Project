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

#include <tr1/memory>

using namespace std;

class AbstractNumber: public tr1::enable_shared_from_this<AbstractNumber> {
public:
	virtual tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>number) = 0;
	virtual tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>number) = 0;
	virtual tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>number) = 0;
	virtual string toString() = 0;
	virtual double toDouble() = 0;
	virtual tr1::shared_ptr<AbstractNumber> simplify() = 0;
	virtual string getName() = 0;
	virtual char getSign() = 0;
	virtual tr1::shared_ptr<AbstractNumber> getValue(string name) = 0;
	virtual tr1::shared_ptr<AbstractNumber> noSign() = 0;

	tr1::shared_ptr<AbstractNumber>base, root, value;
	vector<tr1::shared_ptr<AbstractNumber> > expression, numerator, denominator;

};



#endif /* ABSTRACTNUMBER_H_ */


// Exceptions for the class AbstractNumber
struct NumException : exception {

		// Constructor for NumException
		//
		// Parameters:
		// char* errorMessage	message to be displayed when an exception occurs
		NumException(const char* errorMessage){
			this->errorMessage = errorMessage;
		}

		// Destructor that is stopping a compilation error
		// No clue what it's doing but it's working
		~NumException() throw(){
		}

		// Overrides the what function for meaningful notes
		//
		// Returns:
		// const char*			message to be displayed when an exception occurs
		const char* what() const throw(){
		  return errorMessage;
		}

		const char* errorMessage;		//message to be displayed when an exception occurs
};
