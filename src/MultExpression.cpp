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

void MultExpression::split(vector<tr1::shared_ptr<AbstractNumber> > &num, vector<tr1::shared_ptr<AbstractNumber> > &den, const string &text, char sep1, char sep2) {

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

MultExpression::MultExpression(vector<tr1::shared_ptr<AbstractNumber> > nums , vector<tr1::shared_ptr<AbstractNumber> > dem) {
	this->numerator = nums;
	this->denominator = dem;
}

MultExpression::MultExpression(vector<tr1::shared_ptr<AbstractNumber> > nums)
{
	this->numerator = nums;
}

tr1::shared_ptr<AbstractNumber> MultExpression::multiply(tr1::shared_ptr<AbstractNumber>number)
{
    vector< tr1::shared_ptr<AbstractNumber> > SumTerms = expression;
    SumTerms.push_back(number);
    tr1::shared_ptr<AbstractNumber> tmp;
    for (int i=0; (unsigned)i < SumTerms.size(); i++)
    {
        cout << SumTerms[SumTerms.size() - 1]->toString() << endl;
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

char MultExpression::getSign()
{
	return sign;
}


MultExpression::~MultExpression() {
	// TODO Auto-generated destructor stub
}

tr1::shared_ptr<AbstractNumber> MultExpression::add(tr1::shared_ptr<AbstractNumber>number){

}

tr1::shared_ptr<AbstractNumber> MultExpression::divide(tr1::shared_ptr<AbstractNumber>number){

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

tr1::shared_ptr<AbstractNumber> MultExpression::simplify()
{
    tr1::shared_ptr<AbstractNumber> tmp;
    AbstractNumber* tmp2;
    vector<tr1::shared_ptr<AbstractNumber> > num;
    vector<tr1::shared_ptr<AbstractNumber> > den;

    if (toDouble() == round(toDouble()))
    {
        return tr1::shared_ptr<AbstractNumber>(new SmartInteger(toDouble()));
    }
    numerator = simplifyVector(numerator);
    denominator = simplifyVector(denominator);

    for (int i=0; i < numerator.size(); i++)
    {
        for (int j=i; j < numerator.size(); j++)
        {
            tmp = numerator[i]->divide(denominator[j]);
            if (tmp->getName() != "MultExpression")
            {
                numerator[i] = tmp;
                denominator.erase(denominator.begin() + j);
            }
            else
            {
                num.push_back(numerator[i]);
                den.push_back(denominator[j]);
                MultExpression M = MultExpression(num, den);
                tmp2 = &M;
                if ((tmp->toString()).compare(tmp2->toString()) != 0) //compare, when true, returns 0
                {
                    numerator[i] = tmp;
                    denominator.erase(denominator.begin() + j);
                }
            }
        }
    }
    if (numerator.size() == 1 || denominator.size() == 1)
    {
        if (numerator.size() == 0)
        {
            return denominator[0];
        }
        if (denominator.size() == 0)
        {
            return numerator[0];
        }
    }

    return shared_from_this();
}

vector <tr1::shared_ptr<AbstractNumber> >
MultExpression::simplifyVector(vector <tr1::shared_ptr<AbstractNumber> > vec)
{
    for (int i=0; (unsigned)i < vec.size(); i++)
    {
        vec[i] = vec[i]->simplify();
    }

    if (vec.size() != 1)
    {
        for (int i=0; (unsigned) i < vec.size(); i++)
        {
            for (int j=i+1; (unsigned) j < vec.size(); j++)
            {
                vec[i] = vec[i]->multiply(vec[j]);
                vec.erase(vec.begin() + j);
                if (vec.size() != 1)
                {
                    j = j - 1;
                }
            }

        }
    }

    return vec;
}
string MultExpression::getName()
{
	return "MultExpression";
}
void MultExpression::appendNumberFromString(string input, vector<tr1::shared_ptr<AbstractNumber> > &express)
{
	stringstream ss;
	int num;
	if (input[0] == 'l' && input[1] =='o' && input[2] == 'g' && input[3] == '_' && findOutside(':', input) != string::npos)
	{
		tr1::shared_ptr<AbstractNumber> base(new SumExpression( input.substr(4, findOutside(':',input)-4)));
		cout << "value substring: " << reduceString(input.substr( findOutside(':', input) + 1 , input.size())) << endl;
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1 , input.size() - findOutside(':', input))));

		cout << input << " is a log" << endl;
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Log(base, value)));

	}
	else if (input[0] == 'l' && input[1] == 'n' && input[2] == ':')
	{
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1 , input.size())));
		tr1::shared_ptr<AbstractNumber> base(new E());
		cout << input << " is ln" << endl;
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Log(base, value)));
	}
	else if (input[0] == 's' && input[1] == 'q' && input[2] == 'r' && input[3] == 't' && input[4] == ':')
	{

		cout << input << " is a square root" << endl;
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1, input.size())));
		tr1::shared_ptr<AbstractNumber> root(new SmartInteger("2"));
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Radical(value, root)));
	}
	else if(input[findOutside('r', input)+1] == 't' && input[findOutside('r', input)+2] == ':'){
		cout << input << " is an nth root" << endl;

		tr1::shared_ptr<AbstractNumber> root(new SumExpression(input.substr(0 , findOutside('r', input))));
		tr1::shared_ptr<AbstractNumber> value(new SumExpression(input.substr(findOutside(':', input)+1, input.size())));

		express.push_back(tr1::shared_ptr<AbstractNumber>(new Radical(value, root)));
	}
	else if (input[0] == '(' && input[input.size()-1] ==')')
	{
		cout << input << " is a SumExpression" << endl;
		input.erase(0,1);
		input.erase(input.size()-1,1);

		express.push_back(tr1::shared_ptr<AbstractNumber>(new SumExpression(input)));
	}
	else if (input[0] == 'e' && input.size() == 1)
	{
		express.push_back(tr1::shared_ptr<AbstractNumber>(new E()));
	}
	else if (input[0] == 'p' && input[1] == 'i' && input.size() == 2)
	{
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Pi()));
	}
	else if (isNumber(input))
	{
		cout << input << " is an Integer" << endl;
		express.push_back(tr1::shared_ptr<AbstractNumber>(new SmartInteger(input)));
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
