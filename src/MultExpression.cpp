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
	  cout << "TotalMultExpression Input: " << text  << endl;
	  //This chunk pulls out the string from the  without the * or /
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

	  while (findOutside(sep1, s) != string::npos || findOutside(sep2, s) != string::npos) {
		  hasSign = 1;
		  if (findOutside(sep1, s) < findOutside(sep2, s))
		  {
			  pos = findOutside(sep1, s);

			  if (s.substr(0 , pos)[0] != '+' && s.substr(0 , pos)[0] != '-' && s.substr(0 , pos)[0] != '*' && s.substr(0 , pos)[0] != '/' ){ //May want to try with skipUntil instead of zero, not sure at the moment
					hasSign = 0;
			  }

		  }
		  else {
			  pos = findOutside(sep2, s);
			  if (s.substr(0 , pos)[0] != '+' && s.substr(0 , pos)[0] != '-' && s.substr(0 , pos)[0] != '*' && s.substr(0 , pos)[0] != '/' ){
			  					hasSign = 0;
			  			  }
		  }

		  //Creates an AbstractNumber in the numerator or denominator vector
		  substring = s.substr(hasSign, pos-hasSign);

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
    cout << "MULTEXPRESSION ADDING: " + number->getName();
    cout << " " + number->toString() << endl;

    double d = 1;
    double e = 1;
    if (number->getName() == "SumExpression")
    {
        tr1::shared_ptr<SumExpression> tmpSum = tr1::static_pointer_cast<SumExpression>(number);
        vector<tr1::shared_ptr<AbstractNumber> > express = tmpSum->getExpression();
        for (int i=0; i<express.size(); i++)
        {

        }
    }
    if (number->getName() == "MultExpression")
    {
        tr1::shared_ptr<MultExpression> tmpMult = tr1::static_pointer_cast<MultExpression>(number);
        vector < tr1::shared_ptr<AbstractNumber> > numberNumerator = tmpMult->getNumerator();
        vector < tr1::shared_ptr<AbstractNumber> > numberDenominator = tmpMult->getDenominator();
        if (numerator.size() == 1 && denominator.size() == 1 &&
            numberNumerator.size() == 1 && numberDenominator.size() == 1)
        {
            if (numerator[0]->getName() == "Integer" && denominator[0]->getName() == "Integer" &&
                numberNumerator[0]->getName() == "Integer" && numberDenominator[0]->getName() == "Integer")
            {
                int numValue = (int)(numerator[0]->toDouble() * numberDenominator[0]->toDouble()
                                     + numberNumerator[0]->toDouble() * denominator[0]->toDouble());
                int demValue = (int)(denominator[0]->toDouble() * numberDenominator[0]->toDouble());
                int commonFactor = GCF(numValue, demValue);
                numValue = numValue/commonFactor;
                demValue = demValue/commonFactor;
                tr1::shared_ptr<AbstractNumber> intNum(new SmartInteger(numValue));
                tr1::shared_ptr<AbstractNumber> intDem(new SmartInteger(demValue));
                return tr1::shared_ptr<AbstractNumber>(new MultExpression(intNum, intDem, '+'));
            }
        }
        for (int i=0; i<numberDenominator.size(); i++)
        {
            d = d * numberDenominator[i]->toDouble();
        }
        for (int i=0; i<denominator.size(); i++)
        {
            e = e * denominator[i]->toDouble();
        }

        if (abs(d - e) < 0.000001)
        {
            cout << "DENOMINATORS EQUAL" << endl;
            vector< tr1::shared_ptr<AbstractNumber> > mFinal;
            for (int i=0; i<numerator.size(); i++)
            {
                for (int j=0; j<numberNumerator.size(); j++)
                {
                    tr1::shared_ptr<AbstractNumber> tmpDivide = numerator[i]->divide(numberNumerator[j]);
                    if (tmpDivide->getName() != "MultExpression")
                    {
                        cout << "Factor: " + numberNumerator[j]->toString() << endl;
                        mFinal.push_back(numberNumerator[j]);
                        tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
                        numberNumerator[j] = one;
                        numerator[i] = tmpDivide;
                    }

                    else
                    {
                        tmpDivide = numberNumerator[j]->divide(numerator[i]);
                        if (tmpDivide->getName() != "MultExpression")
                        {
                            cout << "Factor: " + numerator[i]->toString() << endl;
                            mFinal.push_back(numerator[i]);
                            tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
                            numberNumerator[j] = tmpDivide;
                            numerator[i] = one;
                        }
                    }
                }
            }
            numberNumerator = simplifyVector(numberNumerator);
            numerator = simplifyVector(numerator);
            vector< tr1::shared_ptr<AbstractNumber> > sumFinal;
            sumFinal.push_back(numberNumerator[0]);
            sumFinal.push_back(numerator[0]);
            double test = sumFinal[0]->toDouble() + sumFinal[1]->toDouble();
            if (test == round(test))
            {
                tr1::shared_ptr<AbstractNumber> int1(new SmartInteger((int)test));
                mFinal.push_back(int1);
            }
            else
            {
                tr1::shared_ptr<AbstractNumber> sumFinalExp(new SumExpression(sumFinal));
                mFinal.push_back(sumFinalExp);
            }


            tr1::shared_ptr<AbstractNumber> mFinalP(new MultExpression(mFinal, denominator, '+'));

            return mFinalP;
        }
    }

    if ( (number->getName() != "SumExpression") && (number->getName() != "MultExpression") && (number->getName() != "Integer") )
    {
        for (int i=0; i<numerator.size(); i++)
        {
            cout << "NUMERATOR SIZE: ";
            cout << numerator.size() << endl;

            if (abs(numerator[i]->toDouble() - number->toDouble()) < 0.00001)
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
    cout << "Multiplying MultExpression: " + toString();
    cout << " and " + number->toString() << endl;
    if (number->getName() == "SumExpression")
    {
        return number->multiply(shared_from_this());
    }
    if (number->getName() == "MultExpression")
    {
        tr1::shared_ptr<MultExpression> numMult = tr1::static_pointer_cast<MultExpression>(number);
        vector<tr1::shared_ptr<AbstractNumber> > numNumerator = numMult->getNumerator();
        vector<tr1::shared_ptr<AbstractNumber> > numDenominator = numMult->getDenominator();
        for (int i=0; i<numNumerator.size(); i++)
            numerator.push_back(numNumerator[i]);
        for (int i=0; i<numDenominator.size(); i++)
            denominator.push_back(numDenominator[i]);
        numerator = simplifyVector(numerator);
        denominator = simplifyVector(denominator);
        return shared_from_this();
    }
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
    tr1::shared_ptr<AbstractNumber> finalMult(new MultExpression(MultTerms, denominator, '+'));
	if (this->sign == number->getSign())
	{
	    tr1::shared_ptr<AbstractNumber> finalMult(new MultExpression(MultTerms, denominator, '+'));
		return finalMult;
	}
	else{
        tr1::shared_ptr<AbstractNumber> finalMult(new MultExpression(MultTerms, denominator, '-'));
		return finalMult;
	}

}

tr1::shared_ptr<AbstractNumber> MultExpression::divide(tr1::shared_ptr<AbstractNumber> number){
    cout << "Dividing MultExpression: " + toString();
    cout << " and " + number->toString() << endl;

    vector< tr1::shared_ptr<AbstractNumber> > MultTerms = denominator;
    MultTerms.push_back(number->simplify());

    for (int i=0; (unsigned)i < numerator.size(); i++)
    {
        if (numerator[i]->toDouble() == number->toDouble())
        {
            numerator.erase(numerator.begin() + i);
            return shared_from_this();
        }
    }
    for (int i=0; (unsigned)i < numerator.size(); i++)
    {
        tr1::shared_ptr<AbstractNumber> tmpDivide;
        tmpDivide = numerator[i]->divide(number);
        tmpDivide = tmpDivide->simplify();

        if (tmpDivide->getName() != "MultExpression")
        {
            numerator[i] = tmpDivide;
            return shared_from_this();
        }

        tr1::shared_ptr<AbstractNumber> tmpDivide2;
        tmpDivide2 = number->divide(numerator[i]);
        tmpDivide2 = tmpDivide2->simplify();

        if (tmpDivide2->getName() != "MultExpression")
        {
            if (numerator.size() > 1)
            {
                numerator.erase(numerator.begin() + i);
            }
            else
            {
                tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
                numerator[i] = one;
            }

            denominator.push_back(tmpDivide2);
            return shared_from_this();
        }
        if (tmpDivide->getName() == "MultExpression")
        {
            tr1::shared_ptr<MultExpression> tmpMult = tr1::static_pointer_cast<MultExpression>(tmpDivide);
            vector<tr1::shared_ptr<AbstractNumber> > tmpNumerator = tmpMult->getNumerator();
            vector<tr1::shared_ptr<AbstractNumber> > tmpDenominator = tmpMult->getDenominator();
            if (tmpNumerator.size() > 0 && tmpDenominator.size() > 0)
            {
                if (tmpNumerator[0]->getName() == "Integer" && tmpDenominator[0]->getName() == "Integer")
                {
                    numerator[i] = tmpNumerator[0];
                    MultTerms[MultTerms.size() - 1] = tmpDenominator[0];
                }
            }
        }
    }
    tr1::shared_ptr<AbstractNumber> tmp;
    for (int i=0; (unsigned)i < MultTerms.size() - 1; i++)
    {
        if (MultTerms[i]->getName() == MultTerms[MultTerms.size() - 1]->getName())
        {
            if (MultTerms[i]->getName() != "MultExpression")
            {
                tmp = MultTerms[i]->divide(MultTerms[MultTerms.size() - 1]);

                if (tmp->getName() != "MultExpression")
                {
                    MultTerms[i] = tmp;
                    MultTerms.erase(MultTerms.end() - 1);
                }
            }
        }
    }
    tr1::shared_ptr<AbstractNumber> finalMult(new MultExpression(numerator, MultTerms, '+'));
	if (this->sign == number->getSign())
	{
	    tr1::shared_ptr<AbstractNumber> finalMult(new MultExpression(numerator, MultTerms, '+'));
		return finalMult;
	}
	else{
        tr1::shared_ptr<AbstractNumber> finalMult(new MultExpression(numerator, MultTerms, '-'));
		return finalMult;
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
	bool hasZero = false;
	if (getSign() == '-')
	{
		output+='-';
	}

	for (int i =0; i < numerator.size(); i++){
        if (numerator[i]->toDouble() == 0)
        {
            hasZero = true;
            break;
        }
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
	if (hasZero)
        output = '0';
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
    cout <<"SIGN: ";
    cout << sign << endl;
    tr1::shared_ptr<AbstractNumber> tmp;
    if (denominator.size() > 0)
    {
        for (int i=0; i < denominator.size(); i++)
        {
            if (denominator[i]->toDouble() == 0)
                throw "Can't divide by zero.";
        }
    }
    if (toDouble() == round(toDouble()))
    {
        return tr1::shared_ptr<AbstractNumber>(new SmartInteger(toDouble()));
    }
    numerator = simplifyVector(numerator);
    cout << "NUMERATOR: " + numerator[0]->toString() << endl;
    denominator = simplifyVector(denominator);
    if (denominator.size() > 0)
    {
        cout << "DENOMINATOR: " + denominator[0]->toString() << endl;
    }

    if (denominator.size() != 0)
    {
        cout << denominator[0]->toString() << endl;
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
        cout << "MULTIPLYING: " + vec[0]->toString();
        cout << " and " + vec[1]->toString() << endl;
        vec[0] = vec[0]->multiply(vec[1]);
        cout << "FINAL SIMPLIFICATION: " + vec[0]->toString() << endl;
        cout << vec[0]->toDouble() << endl;
        vec.erase(vec.begin() + 1);
    }
    if (sign == '-' && vec.size() > 0)
    {
        tr1::shared_ptr<AbstractNumber> minus_one(new SmartInteger(-1));
        vec[0] = vec[0]->multiply(minus_one);
    }
    return vec;
}
int MultExpression::GCF(int x, int y)
{
    int a;

    a = abs(x - y);
    for (int i = 2; i<=a; i++)
    {
        if ((x%i == 0) && (y%i == 0))
        {
            return i * GCF(x/i, y/i);
        }
    }
    return 1;
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
