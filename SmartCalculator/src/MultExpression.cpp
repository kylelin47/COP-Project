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

}

MultExpression::MultExpression(const string &input) {

	split(numerator, denominator, input, '*', '/');

}

char MultExpression::getSign()
{
	return sign;
}


MultExpression::~MultExpression() {
	// TODO Auto-generated destructor stub
}

vector<AbstractNumber*> MultExpression::add(AbstractNumber *number){

}
vector<AbstractNumber*> MultExpression::multiply(AbstractNumber *number){

}
vector<AbstractNumber*> MultExpression::divide(AbstractNumber *number){

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

double MultExpression::toDouble()
{
	return 0;
}

bool MultExpression::simplify()
{
	return false;
}
string MultExpression::getName()
{
	return "MultExpression";
}
int MultExpression::getTypeFromString(string input)
{
	return SMART_INTEGER;
}

