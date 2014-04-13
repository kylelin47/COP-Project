/*
 * SumExpression.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */
#include "SumExpression.h"

using namespace std;

extern string history;

void SumExpression::split(vector< tr1::shared_ptr<AbstractNumber> > &tokens, const string &text, char sep1, char sep2) {
	cout << history << endl;
  size_t pos = 0;
  size_t skipUntil = 0;
  string s = text;
  string sign = "";
  s += '+';
  if (text[0] == '+' || text[0] == '-')
  {
	  sign = text[0];
	  s.erase(0,1);
  }
  if (s[0] == '(' && s[s.size()-1] == ')')
  	{
  		cout << "Before reduce: " << s << endl;
  		s.erase(0,1);
  		s.erase(s.size()-1,1);
  	}
  	cout << "Reduced String: " << s << endl;


  while ((s.find(sep1, skipUntil)) != string::npos || (s.find(sep2, skipUntil)) != string::npos) {
	  if (s.find(sep1, skipUntil) < s.find(sep2, skipUntil))
	  {
		  pos = s.find(sep1, skipUntil);
	  }
	  else {
		  pos = s.find(sep2, skipUntil);
	  }

	  //cout << "Working Substring: " << s.substr(0,pos) << endl;

	  if (count(s.substr(0 , pos), 0, pos, '(') > count(s.substr(0 , pos), 0, pos, ')'))
	  {
		  skipUntil = pos + 1;
		  //cout << "Skipping until " << skipUntil << endl;
	  }
	  else
	  {
		  //cout << "Substring:" << s.substr(0 , pos) << endl;
		  tr1::shared_ptr<AbstractNumber> n (new MultExpression(sign + s.substr(0 , pos)));
		  this->expression.push_back(n);

		  sign = s[pos];
		  s.erase(0, pos+ 1);
		  skipUntil = 0;
	  }
	}

}
char SumExpression::getSign()
{
	return '+';
}
SumExpression::SumExpression(const string &input) {

	split(expression, makeStringUsable(input), '+' , '-');
	this->noParenthesis = false;
	int number;
}
SumExpression::SumExpression(tr1::shared_ptr<AbstractNumber> number1, tr1::shared_ptr<AbstractNumber> number2)
{
    expression.push_back(number1);
    expression.push_back(number2);
    this->noParenthesis = false;
}
SumExpression::SumExpression::SumExpression(const string &input, bool noParenthesis) {
	split(expression, makeStringUsable(input), '+' , '-');
	this->noParenthesis = noParenthesis;
}

SumExpression::SumExpression(vector<tr1::shared_ptr<AbstractNumber> > &expression) {
    this->expression = expression;
	this->noParenthesis = false;
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

SumExpression::SumExpression() {

}

SumExpression::~SumExpression() {
	// TODO Auto-generated destructor stub
}

tr1::shared_ptr<AbstractNumber> SumExpression::add(tr1::shared_ptr<AbstractNumber>number){
    cout << "ADDING SUM TERMS" << endl;
    vector< tr1::shared_ptr<AbstractNumber> > SumTerms = expression;
    SumTerms.push_back(number->simplify());
    tr1::shared_ptr<AbstractNumber> tmp;
    for (int i=0; (unsigned)i < SumTerms.size() - 1; i++)
    {
        if (SumTerms[i]->getName() == SumTerms[SumTerms.size() - 1]->getName())
        {
            if (SumTerms[i]->getName() != "SumExpression")
            {
                tmp = SumTerms[i]->add(SumTerms[SumTerms.size() - 1]);

                if (tmp->getName() != "SumExpression")
                {
                    SumTerms[i] = tmp;
                    SumTerms.erase(SumTerms.end() - 1);
                }
            }
        }
    }
    expression = SumTerms;
    return shared_from_this();
}

tr1::shared_ptr<AbstractNumber> SumExpression::multiply(tr1::shared_ptr<AbstractNumber>number){

	vector<tr1::shared_ptr<AbstractNumber> > output = expression;
	for (int i = 0; i < output.size() - 1; i++)
	{
		output[i] = output[i]->multiply(number);
	}

	return tr1::shared_ptr<AbstractNumber>(new SumExpression(output));
}

tr1::shared_ptr<AbstractNumber> SumExpression::divide(tr1::shared_ptr<AbstractNumber>number){
	vector<tr1::shared_ptr<AbstractNumber> > output = expression;
	for (int i = 0; i < output.size(); i++)
	{
		output[i] = output[i]->divide(number);
	}

	return tr1::shared_ptr<AbstractNumber>(new SumExpression(output));
}
string SumExpression::toString(){
	string output ="";
	if (!noParenthesis)
	{
		output+='(';
	}

	for (int i =0; i < expression.size(); i++){
		if (expression[i]->getSign() == '+')
		{
			output += expression[i]->getSign();
			output += expression[i]->toString();
		}
		else
		{
			output += expression[i]->toString();
		}

	}
	if (!noParenthesis && output[1] == '+')
	{
		output.erase(1,1);
	}
	if (output[0] == '+')
	{
		if (output[1] == '+')
		{
				output.erase(0,2);
		}
		else {
			output.erase(0,1);
		}
	}
	if (!noParenthesis)
	{
		output += ")";
	}
	return output;
}

double SumExpression::toDouble()
{
    double x = 0;
    for (int i=0; (unsigned)i < expression.size(); i++)
    {
        x = x + expression[i]->toDouble();
    }
	return x;
}

tr1::shared_ptr<AbstractNumber> SumExpression::simplify()
{
    expression = simplifyVector(expression);
    if (expression[0]->getName() == "SumExpression")
    {
        tr1::shared_ptr<SumExpression> tmp = tr1::static_pointer_cast<SumExpression>(expression[0]);
        vector <tr1::shared_ptr<AbstractNumber> > tmpExp = tmp->getExpression();
        if (tmpExp.size() == 1 && tmpExp[0]->getName() != "SumExpression")
        {
            return tmpExp[0];
        }
    }
    else
    {
        return expression[0];
    }
    return expression[0];
}

vector<tr1::shared_ptr<AbstractNumber> > SumExpression::simplifyVector(vector<tr1::shared_ptr<AbstractNumber> > vec)
{
    for (int i=0; (unsigned)i < vec.size(); i++)
    {
        vec[i] = vec[i]->simplify();
    }

    while (vec.size() > 1)
    {
        vec[0] = vec[0]->add(vec[1]);
        vec.erase(vec.begin() + 1);
    }

    return vec;
}
string SumExpression::getName()
{
	return "SumExpression";
}
vector<tr1::shared_ptr<AbstractNumber> > SumExpression::getExpression()
{
    return expression;
}
string SumExpression::makeStringUsable(string input)
{
	string output = input;
	size_t end = input.size();
	string checkPar = output;

	//make sure the parenthesis are in check
	end = output.size();
	//compare parten

	for (size_t i = 0; i < end; i++) //luckly none the places we want to split at share any charactors
		{
			if (checkPar[i] == '(') //make sure the split point is not already signed
			{
				//sketchy error handling
				for (size_t j = i; j < end; j++){
					if (checkPar[j] == ')')
					{
						checkPar.erase(j,1);
						end--;
						j = end;
					}
					if (j == (end - 1)){
						throw "ERROR: Uneven Parentheses";
					}
				}

			}
			if (checkPar[i] == ')')
			{
				throw "ERROR: Uneven Parentheses";
			}



		}


	end = output.size();

	for (size_t i = 0; i < end-1; i++)
	{
		if ((	output[i] == '*' || //l for log
				output[i] == '/' || //p for pi
				output[i] == '+' || //e is e
				output[i] == '^' || //e is e
				output[i] == '-' ) //a for ans
				&& (
				output[i+1] == '^'  ||
				output[i+1] == '*'  ||
				output[i+1] == '/'  ||
				output[i+1] == '+'  ||
				output[i+1] == '-'  )) //make sure the split point is not already signed
		{
			throw "ERROR: Double Operator";
		}
	}

	for (size_t i = 0; i < end-1; i++)
	{
		if (output[i] == ' ')
		{
			output.erase(i,1);
			--i;
			--end;
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
				&& output[i-1] != '*' && output[i-1] != '/' && output[i-1] != '+' && output[i-1] != '-' && output[i-1] != '(' && output[i-1] != ':' && output[i-1] != '_' && output[i-1] != '^') //make sure the split point is not already signed
		{
			output.insert(i,"*");
			i++;
			end++;
		}



	}
	for (size_t i = 0; i < end - 1; i++)
	{
		if (output[i] == ')' && (output[i+1] != '*' && output[i+1] != '/' && output[i+1] != '+' && output[i+1] != '-' && output[i+1] != ':' && output[i+1] != '^'))
		{
			output.insert(i+1, "*");
			end++;
		}
	}
	//cout << "Usable string: "<< output << endl << endl;
	return output;
}

tr1::shared_ptr<AbstractNumber> SumExpression::getValue(string name){

	throw "tried to get a " + name + " from a SumExpression";

}

tr1::shared_ptr<AbstractNumber> SumExpression::noSign()
{
	tr1::shared_ptr<AbstractNumber> output(new SumExpression(expression));
	return output;
}
