/*
 * SumExpression.h
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#ifndef SUMEXPRESSION_H_
#define SUMEXPRESSION_H_
#include "MultExpression.h"

using namespace std;

class SumExpression: public AbstractNumber {
public:
	SumExpression(vector< tr1::shared_ptr<AbstractNumber> > &expression);
	SumExpression(const string &input);
	virtual ~SumExpression();
	tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>number);
	string toString();
	void split(vector< tr1::shared_ptr<AbstractNumber> > &tokens, const string &text, char sep1, char sep2);
	vector< tr1::shared_ptr<AbstractNumber> > expression;
	double toDouble();
	string getName();
	int count(string input, int begin, int end, char symbol);
	string makeStringUsable(string input);

	tr1::shared_ptr<AbstractNumber> simplify();
	char getSign();

};


#endif /* SUMEXPRESSION_H_ */
