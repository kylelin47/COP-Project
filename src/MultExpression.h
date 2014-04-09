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
	MultExpression(vector< tr1::shared_ptr<AbstractNumber> > expression , vector< tr1::shared_ptr<AbstractNumber> > dem);
	MultExpression(vector< tr1::shared_ptr<AbstractNumber> > expression);
	virtual ~MultExpression();
	tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>number);
	string toString();
	void split(vector< tr1::shared_ptr<AbstractNumber> > &num, vector< tr1::shared_ptr<AbstractNumber> > &den, const string &text, char sep1, char sep2);
	//vector<string> expression;
	vector< tr1::shared_ptr<AbstractNumber> > numerator;
	vector< tr1::shared_ptr<AbstractNumber> > denominator;
	char getSign();
	double toDouble();
	 tr1::shared_ptr<AbstractNumber>  simplify();
	string getName();
	int getTypeFromString(string input);
	int count(string input, int begin, int end, char symbol);

	vector < tr1::shared_ptr<AbstractNumber> > expression;

private:
	char sign;
};


#endif /* MultExpression_H_ */
