/*
 * MultExpression.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#include "MultExpression.h"
//#include <Algorithm>
#include "Log.h"
#include "E.h"
#include "Pi.h"
#include "Radical.h"
#include "SumExpression.h"
#include "Exponent.h"
#define SMART_INTEGER 1
#define SMART_POWER 2
#define SMART_LOG 4
#define SMART_LN 5
#define SMART_FLOAT 8
#define SMART_PI 16
#define SMART_E 32


using namespace std;

//Testing to see if this works

extern string history;

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

				  cout << "adding " << substring << " to the denominator" << endl;
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

MultExpression::MultExpression()
{
    this->sign = '+';
}

MultExpression::MultExpression(tr1::shared_ptr<AbstractNumber> numerator, tr1::shared_ptr<AbstractNumber> denominator, char sign)
{
    this->numerator.push_back(numerator);
    this->denominator.push_back(denominator);
    this->sign = sign;
}

MultExpression::MultExpression(vector<tr1::shared_ptr<AbstractNumber> > nums , vector<tr1::shared_ptr<AbstractNumber> > dem, char sign) {
	numerator = nums;
	denominator = dem;
	this->sign = sign;
}


MultExpression::MultExpression(vector<tr1::shared_ptr<AbstractNumber> > nums, char sign)
{
	numerator = nums;
	this->sign = sign;
}

tr1::shared_ptr<AbstractNumber> MultExpression::add(tr1::shared_ptr<AbstractNumber> number)
{
    cout << "MULTEXPRESSION ADDING: " + number->getName() << endl;
    double d = 1;
    double e = 1;
    if (number->getName() == "MultExpression")
    {
        for (int i=0; i<number->denominator.size(); i++)
        {
            d = d * number->denominator[i]->toDouble();
        }
        for (int i=0; i<numerator.size(); i++)
        {
            e = e * numerator[i]->toDouble();
        }
        if (d == e)
        {
            vector < tr1::shared_ptr<AbstractNumber> > factors;
            for (int i=0; i<number->numerator.size(); i++)
            {
                for (int i=0; i<numerator.size(); i++)
                {
                    for (int j=0; j<number->numerator.size(); j++)
                    {
                        tr1::shared_ptr<AbstractNumber> tmpDivide = numerator[i]->divide(number->numerator[j]);
                        if (tmpDivide->getName() != "MultExpression")
                        {
                            factors.push_back(tmpDivide);

                            numerator[i] = tmpDivide;
                            number->numerator.erase(number->numerator.begin() + j);
                            i = i - 1;
                            j = j - 1;
                        }
                        tmpDivide = number->numerator[j]->divide(numerator[i]);
                        if (tmpDivide->getName() != "MultExpression")
                        {
                            factors.push_back(tmpDivide);

                            number->numerator[j] = tmpDivide;
                            numerator.erase(numerator.begin() + i);
                            i = i - 1;
                            j = j - 1;
                        }
                    }
                }

                vector< tr1::shared_ptr<AbstractNumber> > m;
                m.push_back(tr1::shared_ptr<AbstractNumber>(new MultExpression(factors, '+')));

                vector< tr1::shared_ptr<AbstractNumber> > s;
                s.push_back(tr1::shared_ptr<AbstractNumber>(new MultExpression(numerator, '+')));
                s.push_back(tr1::shared_ptr<AbstractNumber>(new MultExpression(number->numerator, '+')));
                if (s[0]->getName() != "MultExpression")
                {
                    s[0] = s[0]->add(s[1]);
                    s.erase(s.begin() + 1);
                }
                tr1::shared_ptr<AbstractNumber> SimplifiedSum(new SumExpression(s));
                tr1::shared_ptr<AbstractNumber> SimpleMult(new MultExpression(m, '+'));
                SimpleMult->numerator.push_back(SimplifiedSum);
                SimpleMult->denominator = denominator;
                return SimpleMult;
            }
        }
    }

    if ( (number->getName() != "SumExpression") && (number->getName() != "MultExpression") )
    {
        for (int i=0; i<numerator.size(); i++)
        {
            cout << "NUMERATOR SIZE: ";
            cout << numerator.size() << endl;
            if (numerator[i]->toDouble() == number->toDouble())
            {
                tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
                for(int j=0; j<numerator.size(); j++)
                {
                    if (numerator[j]->getName() == "Integer")
                    {
                        numerator[j] = numerator[j]->add(one);
                        return shared_from_this();
                    }
                }
                numerator[i] = numerator[i]->add(one);
                return shared_from_this();
            }
        }
    }

    vector< tr1::shared_ptr<AbstractNumber> > s;
    s.push_back(shared_from_this());
    s.push_back(number);
    cout << number->toDouble() << endl;
    return tr1::shared_ptr<AbstractNumber>(new SumExpression(s));
}
tr1::shared_ptr<AbstractNumber> MultExpression::multiply(tr1::shared_ptr<AbstractNumber>number)
{
    vector< tr1::shared_ptr<AbstractNumber> > MultTerms = numerator;
    MultTerms.push_back(number->simplify());

    tr1::shared_ptr<AbstractNumber> tmp;
    for (int i=0; (unsigned)i < denominator.size(); i++)
    {
        if (denominator[i]->toDouble() == number->toDouble())
        {
            denominator.erase(denominator.begin() + i);
            return shared_from_this();
        }
    }
    for (int i=0; (unsigned)i < MultTerms.size() - 1; i++)
    {
        if (MultTerms[i]->getName() == MultTerms[MultTerms.size() - 1]->getName())
        {
            if (MultTerms[i]->getName() != "MultExpression")
            {
                tmp = MultTerms[i]->multiply(MultTerms[MultTerms.size() - 1]);

                if (tmp->getName() != "MultExpression")
                {
                    MultTerms[i] = tmp;
                    MultTerms.erase(MultTerms.end() - 1);
                }
            }
        }
    }
    expression = MultTerms;

	if (this->sign == number->getSign())
	{
	    sign = '+';
		return shared_from_this();
	}
	else{
        sign = '-';
		return shared_from_this();
	}

}

tr1::shared_ptr<AbstractNumber> MultExpression::divide(tr1::shared_ptr<AbstractNumber> number){
	denominator.push_back(number);

	if (this->sign == number->getSign())
	{
	    sign = '+';
		return shared_from_this();
	}
	else{
        sign = '-';
		return shared_from_this();
	}
}

char MultExpression::getSign()
{
	return sign;
}
vector<tr1::shared_ptr<AbstractNumber> > MultExpression::getNumerator()
{
    return numerator;
}
vector<tr1::shared_ptr<AbstractNumber> > MultExpression::getDenominator()
{
    return denominator;
}
MultExpression::~MultExpression() {
	// TODO Auto-generated destructor stub
}

string MultExpression::toString(){
	string output ="";
	if (getSign() == '-')
	{
		output+='-';
	}

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
    for (int i=0; i<numerator.size(); i++)
    {
        x = x * numerator[i]->toDouble();
    }
    for (int i=0; i<denominator.size(); i++)
    {
        x = x / denominator[i]->toDouble();
    }
    if (sign == '-')
    {
        return -x;
    }
	return x;
}

tr1::shared_ptr<AbstractNumber> MultExpression::simplify()
{
    cout <<"SIMPLIFYING MULT EXPRESSION" << endl;

    tr1::shared_ptr<AbstractNumber> tmp;

    if (toDouble() == round(toDouble()))
    {
        return tr1::shared_ptr<AbstractNumber>(new SmartInteger(toDouble()));
    }
    numerator = simplifyVector(numerator);
    cout << "NUMERATOR: " + numerator[0]->toString() << endl;
    denominator = simplifyVector(denominator);
    if (denominator.size() != 0)
    {
        tmp = numerator[0]->divide(denominator[0]);
        if (tmp->getName() != "MultExpression")
        {
            numerator[0] = tmp;
            denominator.erase(denominator.begin());
        }
        else
        {
            if (tmp->toDouble() < 0)
            {
                char sign = '-';
            }
            else
            {
                char sign = '+';
            }
            tr1::shared_ptr<MultExpression> tmpMult = tr1::static_pointer_cast<MultExpression>(tmp);
            vector <tr1::shared_ptr<AbstractNumber> > tmpNumerator = tmpMult->getNumerator();
            vector <tr1::shared_ptr<AbstractNumber> > tmpDenominator = tmpMult->getDenominator();
            for (int i=0; i<tmpNumerator.size(); i++)
            {
                for (int j=0; j<tmpDenominator.size(); j++)
                {
                    tmp = tmpNumerator[i]->divide(tmpDenominator[j]);
                    tmpMult = tr1::static_pointer_cast<MultExpression>(tmp);
                    vector <tr1::shared_ptr<AbstractNumber> > tmpNumerator2 = tmpMult->getNumerator();
                    vector <tr1::shared_ptr<AbstractNumber> > tmpDenominator2 = tmpMult->getDenominator();
                    if (tmpNumerator[i]->toDouble() != tmpNumerator2[0]->toDouble())
                    {
                        tmpNumerator[i] = tmp;
                        tmpDenominator.erase(tmpDenominator.begin() + j);
                    }
                }

            }
            numerator = tmpNumerator;
            denominator = tmpDenominator;
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
    cout << "VECTOR SIZE: ";
    cout << vec.size() << endl;
    for (int i=0; (unsigned)i < vec.size(); i++)
    {
        cout << "SIMPLIFYING: " + vec[i]->toString() << endl;
        vec[i] = vec[i]->simplify();
        cout << "RESULT: " + vec[i]->toString() << endl;

    }

    while (vec.size() > 1)
    {
        cout << "MULTIPLYING: " + vec[0]->getName();
        cout << " and " + vec[1]->getName() << endl;
        vec[0] = vec[0]->multiply(vec[1]);
        cout << "FINAL SIMPLIFICATION: " + vec[0]->toString() << endl;
        vec.erase(vec.begin() + 1);
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
		tr1::shared_ptr<AbstractNumber> base(new SumExpression( input.substr(4, findOutside(':',input)-4) , false));
		cout << "value substring: " << input.substr( findOutside(':', input) + 1 , input.size()) << endl;
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1 , input.size() - findOutside(':', input)) , false));

		cout << input << " is a log" << endl;
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Log(base, value)));

	}
	else if (input[0] == 'l' && input[1] == 'n' && input[2] == ':')
	{
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1 , input.size()), false));
		tr1::shared_ptr<AbstractNumber> base(new E());
		cout << input << " is ln" << endl;
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Log(base, value)));
	}
	else if (input[0] == 'l' && input[1] == 'o' && input[2] == 'g' && input[3] == ':')
	{
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1 , input.size()), false));
		tr1::shared_ptr<AbstractNumber> base(new SmartInteger(10));
		cout << input << " is a log base 10" << endl;
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Log(base, value)));
	}
	else if (input[0] == 's' && input[1] == 'q' && input[2] == 'r' && input[3] == 't' && input[4] == ':')
	{

		cout << input << " is a square root" << endl;
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1, input.size()) , false));
		tr1::shared_ptr<AbstractNumber> root(new SmartInteger("2"));
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Radical(value, root)));
	}
	else if(input[findOutside('r', input)+1] == 't' && input[findOutside('r', input)+2] == ':'){
		cout << input << " is an nth root" << endl;

		tr1::shared_ptr<AbstractNumber> root(new SumExpression(input.substr(0 , findOutside('r', input)) , false));
		tr1::shared_ptr<AbstractNumber> value(new SumExpression(input.substr(findOutside(':', input)+1, input.size()) , false));

		express.push_back(tr1::shared_ptr<AbstractNumber>(new Radical(value, root)));
	}
	else if (findOutside('^', input) != string::npos)
	{
		cout << findOutside('^', input) << endl;
		cout << input << " is a exponent" << endl;
		tr1::shared_ptr<AbstractNumber> base(new SumExpression(input.substr(0 , findOutside('^', input)) , false));
		cout << "step two \n";
		tr1::shared_ptr<AbstractNumber> value(new SumExpression(input.substr(findOutside('^', input)+1, input.size()) , false));
		cout << "step two \n";
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Exponent(base, value)));

	}
	else if (input[0] == 'a' && input[1] == 'n' && input[2] == 's' && input.size() == 3)
	{
		cout << "found and ANSWER" << endl;
		if (history == "")
		{
			throw "No previous answer found";
		}
		express.push_back(tr1::shared_ptr<AbstractNumber>(new SumExpression(history)));
	}
	else if (input[0] == '(' && input[input.size()-1] ==')')
	{
		cout << input << " is a SumExpression" << endl;
		input.erase(0,1);
		input.erase(input.size()-1,1);

		express.push_back(tr1::shared_ptr<AbstractNumber>(new SumExpression(input , false)));
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

tr1::shared_ptr<AbstractNumber> MultExpression::getValue(string name){

	throw "tried to get a " + name + " from a MultExpression";

}
tr1::shared_ptr<AbstractNumber> MultExpression::noSign()
{
	tr1::shared_ptr<AbstractNumber> output(new MultExpression(numerator, denominator, '+'));
	return output;
}
