/*
 * MultExpression.h
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#ifndef MultExpression_H_
#define MultExpression_H_
#include "SmartInteger.h"
#include <iostream>

class MultExpression: public AbstractNumber {
public:
    MultExpression();
    MultExpression(const string &input);
	MultExpression(vector<tr1::shared_ptr<AbstractNumber> > nums , vector<tr1::shared_ptr<AbstractNumber> > dem, char sign);
	MultExpression(vector<tr1::shared_ptr<AbstractNumber> > nums, char sign);
	virtual ~MultExpression();
	tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>number);

	string toString();
	void split(vector<tr1::shared_ptr<AbstractNumber> > &num, vector< tr1::shared_ptr<AbstractNumber> > &den, const string &text, char sep1, char sep2);
	//vector<string> expression;
	vector<tr1::shared_ptr<AbstractNumber> > numerator, denominator;
	char getSign();
	double toDouble();
	tr1::shared_ptr<AbstractNumber> simplify();
    vector<tr1::shared_ptr<AbstractNumber> > simplifyVector(vector<tr1::shared_ptr<AbstractNumber> > vec);
	string getName();
	void appendNumberFromString(string input, vector< tr1::shared_ptr<AbstractNumber> > &express);
	int count(string input, int begin, int end, char symbol);
	bool isNumber(string input);
	string reduceString(string input);
	size_t findOutside(char symbol, string input);

	vector <tr1::shared_ptr<AbstractNumber> > expression;

private:
	char sign;
};


#endif /* MultExpression_H_ */
