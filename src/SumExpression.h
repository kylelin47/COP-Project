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
	SumExpression(const string &input);
	virtual ~SumExpression();
	vector<AbstractNumber*> add(AbstractNumber *number);
	vector<AbstractNumber*> multiply(AbstractNumber *number);
	vector<AbstractNumber*> divide(AbstractNumber *number);
	string toString();
	void split(vector<MultExpression> &tokens, const string &text, char sep1, char sep2);
	vector<MultExpression> expression;
	double toDouble();
	bool simplify();
	string getName();
	int count(string input, int begin, int end, char symbol);
	string makeStringUsable(string input);



};


#endif /* SUMEXPRESSION_H_ */
