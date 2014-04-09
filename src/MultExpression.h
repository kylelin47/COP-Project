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
	MultExpression(vector<AbstractNumber*> nums , vector<AbstractNumber*> dem, char sign);
	MultExpression(vector<AbstractNumber*> nums, char sign);
	virtual ~MultExpression();
	AbstractNumber * add(AbstractNumber *number);
	AbstractNumber * multiply(AbstractNumber *number);
	AbstractNumber * divide(AbstractNumber *number);
	string toString();
	void split(vector<AbstractNumber*> &num, vector<AbstractNumber*> &den, const string &text, char sep1, char sep2);
	//vector<string> expression;
	vector<AbstractNumber*> numerator;
	vector<AbstractNumber*> denominator;
	char getSign();
	double toDouble();
	AbstractNumber* simplify();
	string getName();
	void appendNumberFromString(string input, vector<AbstractNumber*> &express);
	int count(string input, int begin, int end, char symbol);
	bool isNumber(string input);
	string reduceString(string input);
	size_t findOutside(char symbol, string input);
	
	vector <AbstractNumber*> expression;

private:
	char sign;
};


#endif /* MultExpression_H_ */
