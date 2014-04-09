/*
 * MultExpression.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#include "MultExpression.h"
#include <Algorithm>
#include "Log.h"
#include "E.h"
#include "Pi.h"
#include "Radical.h"
#include "SumExpression.h"
#define SMART_INTEGER 1
#define SMART_POWER 2
#define SMART_LOG 4
#define SMART_LN 5
#define SMART_FLOAT 8
#define SMART_PI 16
#define SMART_E 32


using namespace std;

//Testing to see if this works

void MultExpression::split(vector<AbstractNumber*> &num, vector<AbstractNumber*> &den, const string &text, char sep1, char sep2) {

	  //This chunk pulls out the string from the MultExpression without the * or /
	  int hasSign;
	  char nextValue = '*';
	  size_t skipUntil=0;
	  string substring;
	  size_t pos = 0;
	  int type;
	  if (text[0] != '+' && text[0] != '-' ){
	  		sign = '+';
	  }
	  else {
	  		sign = text[0];
	  }
	  string s = text;
	  s += '*';

	  while (s.find(sep1, skipUntil) != string::npos || s.find(sep2, skipUntil) != string::npos) {
		  hasSign = 1;
		  if (s.find(sep1, skipUntil) < s.find(sep2, skipUntil))
		  {
			  pos = s.find(sep1, skipUntil);

			  if (s.substr(0 , pos)[0] != '+' && s.substr(0 , pos)[0] != '-' && s.substr(0 , pos)[0] != '*' && s.substr(0 , pos)[0] != '/' ){ //May want to try with skipUntil instead of zero, not sure at the moment
					hasSign = 0;
			  }

		  }
		  else {
			  pos = s.find(sep2, skipUntil);
			  if (s.substr(0 , pos)[0] != '+' && s.substr(0 , pos)[0] != '-' && s.substr(0 , pos)[0] != '*' && s.substr(0 , pos)[0] != '/' ){
			  					hasSign = 0;
			  			  }
		  }


		  //Creates an AbstractNumber in the numerator or denominator vector
		  substring = s.substr(hasSign, pos-hasSign);

		  if (count(substring, 0, pos, '(') > count(substring, 0, pos, ')'))
		  {
		  		  skipUntil = pos+1;
		  		  //cout << "SkippingMult:" << skipUntil << endl;
		  }
		  else
		  {
			  //cout << "MultSubstring: " << substring << endl;

			  if (nextValue == '*'){
					  appendNumberFromString(substring, numerator);
				  }
			  else {
					 appendNumberFromString(substring, denominator);
				  }

			  nextValue = s[pos];
			  s.erase(0, pos+ 1);
		  }
	}
}


MultExpression::MultExpression(const string &input) {

	split(numerator, denominator, input, '*', '/');
}

MultExpression::MultExpression(vector<AbstractNumber*> nums , vector<AbstractNumber*> dem, char sign) {
	this->numerator = nums;
	this->denominator = dem;
	this->sign = sign;
}

MultExpression::MultExpression(vector<AbstractNumber*> nums, char sign)
{
	this->numerator = nums;
	this->sign = sign;
}

AbstractNumber * MultExpression::multiply(AbstractNumber *number)
{
	if (	number->getName() == "Integer" ||
			number->getName() == "E" ||
			number->getName() == "SumExpression" ||
			number->getName() == "Pi" ||
			number->getName() == "Log" ||
			number->getName() == "Radical" )
	{
		vector<AbstractNumber*> output= numerator;
		output.push_back(number);
		if (this->sign == number->getSign())
		{
			return new MultExpression(output, denominator, '+');
		}
		else{
			return new MultExpression(output, denominator, '-');
		}
	}

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

AbstractNumber * MultExpression::divide(AbstractNumber *number){

}
string MultExpression::toString(){
	string output ="";
		for (int i =0; i < numerator.size(); i++){
			output += numerator[i]->toString();
			if (i < numerator.size()-1)
			{
				output += "*";
			}
		}
		for (int i = 0; i < denominator.size(); i++){
			output += "/";
			output += denominator[i]->toString();

		}
		return output;
}

int MultExpression::count(string input, int begin, int end, char symbol)
{
	int count = 0;
	for (int i = begin; i <= end; i++)
	{
		if (input[i] == symbol)
		{
			count++;
		}
	}
	return count;

}

double MultExpression::toDouble()
{
    double x = 1;

	return x;
}

AbstractNumber* MultExpression::simplify()
{
    vector<AbstractNumber*> SimplifiedTerms;
}
string MultExpression::getName()
{
	return "MultExpression";
}
void MultExpression::appendNumberFromString(string input, vector<AbstractNumber*> &express)
{
	stringstream ss;
	int num;
	if (input[0] == 'l' && input[1] =='o' && input[2] == 'g' && input[3] == '_' && findOutside(':', input) != string::npos)
	{
		AbstractNumber* base = new SumExpression( input.substr(4, findOutside(':',input)-4));
		cout << "value substring: " << reduceString(input.substr( findOutside(':', input) + 1 , input.size())) << endl;
		AbstractNumber* value = new SumExpression( input.substr( findOutside(':', input) + 1 , input.size() - findOutside(':', input)));

		cout << input << " is a log" << endl;
		express.push_back(new Log(base, value));

	}
	else if (input[0] == 'l' && input[1] == 'n' && input[2] == ':')
	{
		AbstractNumber* value = new SumExpression( input.substr( findOutside(':', input) + 1 , input.size()));
		AbstractNumber* base = new E();
		cout << input << " is ln" << endl;
		express.push_back(new Log(base, value));
	}
	else if (input[0] == 's' && input[1] == 'q' && input[2] == 'r' && input[3] == 't' && input[4] == ':')
	{

		cout << input << " is a square root" << endl;
		AbstractNumber* value = new SumExpression( input.substr( findOutside(':', input) + 1, input.size()));
		AbstractNumber* root = new SmartInteger("2");
		express.push_back(new Radical(value, root));
	}
	else if(input[findOutside('r', input)+1] == 't' && input[findOutside('r', input)+2] == ':'){
		cout << input << " is an nth root" << endl;

		AbstractNumber* root = new SumExpression(input.substr(0 , findOutside('r', input)));
		AbstractNumber* value = new SumExpression(input.substr(findOutside(':', input)+1, input.size()));

		express.push_back(new Radical(value, root));
	}
	else if (input[0] == '(' && input[input.size()-1] ==')')
	{
		cout << input << " is a SumExpression" << endl;
		input.erase(0,1);
		input.erase(input.size()-1,1);

		express.push_back(new SumExpression(input));
	}
	else if (input[0] == 'e' && input.size() == 1)
	{
		express.push_back(new E());
	}
	else if (input[0] == 'p' && input[1] == 'i' && input.size() == 2)
	{
		express.push_back(new Pi());
	}
	else if (isNumber(input))
	{
		cout << input << " is an Integer" << endl;
		express.push_back(new SmartInteger(input));
	}
	else
	{
		cout << input << " is not a valid expression" << endl; // THROW here
	}
}

bool MultExpression::isNumber(string input)
{
	for (int i = 0; (unsigned)i < input.size(); i++)
	{
		if (!isdigit(input[i]))
		{
			return false;
		}
	}
	return true;
}

size_t MultExpression::findOutside(char symbol , string input)
{
	size_t pos;
	size_t skipUntil = 0;
	while ((pos = input.find(symbol,skipUntil)) != string::npos)
	{
		if (count(input, 0, pos, '(') > count(input, 0, pos, ')'))
		{
				skipUntil = pos+1;
		}
		else
		{
			return pos;
		}
	}
	return string::npos;
}
