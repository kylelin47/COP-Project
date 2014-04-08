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
  size_t skipUntil = 0;
  string s = text;
  string sign = "";
  s += '+';
  while ((s.find(sep1, skipUntil)) != string::npos || (s.find(sep2, skipUntil)) != string::npos) {
	  if (s.find(sep1, skipUntil) < s.find(sep2, skipUntil))
	  {
		  pos = s.find(sep1, skipUntil);
	  }
	  else {
		  pos = s.find(sep2, skipUntil);
	  }

	  cout << "Working Substring: " << s.substr(0,pos) << endl;

	  if (count(s.substr(0 , pos), 0, pos, '(') > count(s.substr(0 , pos), 0, pos, ')'))
	  {
		  skipUntil = pos + 1;
		  cout << "Skipping until " << skipUntil << endl;
	  }
	  else
	  {
		  cout << "Substring:" << s.substr(0 , pos) << endl;
		  tokens.push_back(MultExpression(sign + s.substr(0 , pos)));

		  sign = s[pos];
		  s.erase(0, pos+ 1);
		  skipUntil = 0;
	  }
	}

}

SumExpression::SumExpression(const string &input) {


	split(expression, makeStringUsable(input), '+' , '-');

}

int SumExpression::count(string input, int begin, int end, char symbol)
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

string SumExpression::makeStringUsable(string input)
{
	cout << "Starting Make String Usable" << endl;
	string output = input;
	size_t end = input.size();

	//make sure the parenthesis are in check
	while (count(output, 0, output.size(), '(') != count(output, 0, output.size(), ')'))
	{
		cout << output << endl;
		if (count(output, 0, end, '(') > count(output, 0, end, ')'))
		{
			output.insert(end,")");
		}
		else
		{
			output.insert(0,"(");
		}
	}
	end = output.size();
	for (size_t i = 1; i < end; i++) //luckly none the places we want to split at share any charactors
	{
		if ((	output[i] == '(' || //break at (
				output[i] == 'l' || //l for log
				output[i] == 'p' || //p for pi
				output[i] == 'e' || //e is e
				output[i] == 'a' ) //a for ans
				&& output[i-1] != '*' && output[i-1] != '/' && output[i-1] != '+' && output[i-1] != '-' && output[i-1] != '(') //make sure the split point is not already signed
		{
			output.insert(i,"*");
			i++;
			end++;
		}



	}
	cout << "Usable string: "<< output << endl << endl;
	return output;
}



