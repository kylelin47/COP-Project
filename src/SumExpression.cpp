/*
 * SumExpression.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

//gsdfagsdagsdagdsgsdagsadgsdag

#include "SumExpression.h"

using namespace std;

void SumExpression::split(vector<MultExpression> &tokens, const string &text, char sep1, char sep2) {
  size_t pos = 0;
  string s = text;
  string sign = "";
  s += '+';
  while ((pos = s.find(sep1)) != string::npos || (pos = s.find(sep2)) != string::npos) {
	  if (s.find(sep1) < s.find(sep2))
	  {
		  pos = s.find(sep1);
	  }
	  else {
		  pos = s.find(sep2);
	  }

	  cout << "Substring:" << s.substr(0 , pos) << endl;
	  tokens.push_back(MultExpression(sign + s.substr(0 , pos)));

	  sign = s[pos];
	  s.erase(0, pos+ 1);
	}



 /*	stringstream ss(text);
	string item;
	while (getline(ss, item, sep1)){

		cout << item << "\n\n";
		tokens.push_back(MultExpression("+" + item));

	}*/

}

SumExpression::SumExpression(const string &input) {

	split(expression, input, '+' , '-');

}



SumExpression::~SumExpression() {
	// TODO Auto-generated destructor stub
}

vector<AbstractNumber*> SumExpression::add(AbstractNumber *number){

}
vector<AbstractNumber*> SumExpression::multiply(AbstractNumber *number){

}
vector<AbstractNumber*> SumExpression::divide(AbstractNumber *number){

}
string SumExpression::toString(){
	string output ="";
	for (int i =0; (unsigned)i < expression.size(); i++){
		output += expression[i].getSign();
		output += expression[i].toString();

	}
	return output;
}

double SumExpression::toDouble()
{
	return 0;
}

bool SumExpression::simplify()
{
	return false;
}
string SumExpression::getName()
{
	return "SumExpression";
}




