/*
 * MultExpression.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#include "MultExpression.h"
#define SMART_INTEGER 1
#define SMART_POWER 2
#define SMART_LOG 4
#define SMART_FLOAT 8
#define SMART_PI 16
#define SMART_E 32


using namespace std;

void MultExpression::split(vector<AbstractNumber*> &num, vector<AbstractNumber*> &den, const string &text, char sep1, char sep2) {
/*
	  //This chunk pulls out the string from the MultExpression without the * or /
	  int hasSign;
	  char nextValue = '*';
	  size_t pos = 0;
	  if (text[0] != '+' && text[0] != '-' ){
	  		sign = '+';
	  }
	  else {
	  		sign = text[0];
	  }
	  string s = text;
	  s += '*';

	  while (s.find(sep1) != string::npos || s.find(sep2) != string::npos) {
		  hasSign = 1;
		  if (s.find(sep1) < s.find(sep2))
		  {
			  pos = s.find(sep1);

			  if (s.substr(0 , pos)[0] != '+' && s.substr(0 , pos)[0] != '-' && s.substr(0 , pos)[0] != '*' && s.substr(0 , pos)[0] != '/' ){
					hasSign = 0;
			  }

		  }
		  else {
			  pos = s.find(sep2);
			  if (s.substr(0 , pos)[0] != '+' && s.substr(0 , pos)[0] != '-' && s.substr(0 , pos)[0] != '*' && s.substr(0 , pos)[0] != '/' ){
			  					hasSign = 0;
			  			  }
		  }


		  //Creates an AbstractNumber in the numerator or denominator vector


		  switch(getTypeFromString(s.substr(hasSign , pos)))
		  {
		  	  case SMART_INTEGER: 		//This is the syntax for adding BaseNumbers
		  		if (nextValue == '*'){
		  			  numerator.push_back(new SmartInteger(s.substr(hasSign , pos)));
				  }
				  else {
					  denominator.push_back(new SmartInteger(s.substr(hasSign , pos)));
				  }
		  		break;
		  }


		  nextValue = s[pos];
		  s.erase(0, pos+ 1);
		  }
*/
}

MultExpression::MultExpression(vector<AbstractNumber*> nums) {

	this->nums = nums;
}

char MultExpression::getSign()
{
	return sign;
}


MultExpression::~MultExpression() {
	// TODO Auto-generated destructor stub
}

AbstractNumber * MultExpression::add(AbstractNumber *number){

}
AbstractNumber * MultExpression::multiply(AbstractNumber *number){

}
AbstractNumber * MultExpression::divide(AbstractNumber *number){

}
string MultExpression::toString(){
	string output ="";
	for (int i =0; (unsigned)i < nums.size(); i++){
		output += nums[i]->toString();
		if ((unsigned)i < nums.size() - 1)
		{
			output += " * ";
		}
	}
	for (int i = 0; (unsigned)i < denominator.size(); i++){
		output += "/";
		output += denominator[i]->toString();

	}
	return output;
}

double MultExpression::toDouble()
{
    double x = 1;

    for (int i=0; (unsigned)i < nums.size(); i++)
    {
        x = x * nums[i]->toDouble();
    }
	return x;
}

AbstractNumber* MultExpression::simplify()
{
    vector<AbstractNumber*> SimplifiedTerms;

    for (int i=0; (unsigned)i < nums.size(); i++)
    {
        SimplifiedTerms.push_back(nums[i]->simplify());
    }
    static MultExpression simpleMult = MultExpression(SimplifiedTerms);
    simpleMult = MultExpression(SimplifiedTerms);

    if (SimplifiedTerms.size() == this->nums.size())
    {
        return &simpleMult;
    }
    else
    {
        return simpleMult.simplify();
    }
}
string MultExpression::getName()
{
	return "MultExpression";
}
int MultExpression::getTypeFromString(string input)
{
	return SMART_INTEGER;
}

