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
	SumExpression(vector<AbstractNumber*> &nums);
	SumExpression(const string &input);
	virtual ~SumExpression();
	AbstractNumber * add(AbstractNumber *number);
	AbstractNumber * multiply(AbstractNumber *number);
	AbstractNumber * divide(AbstractNumber *number);
	string toString();
	void split(vector<MultExpression> &tokens, const string &text, char sep1, char sep2);
	vector<MultExpression> expression;
	double toDouble();
	string getName();
	int count(string input, int begin, int end, char symbol);
	string makeStringUsable(string input);

	AbstractNumber* simplify();

    vector<AbstractNumber*> nums;

};


#endif /* SUMEXPRESSION_H_ */
