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
    if(numerator.size() == 1)
    {
        if (numerator[0]->getName() == "MultExpression")
        {
        	tr1::shared_ptr<MultExpression> realYou = tr1::static_pointer_cast<MultExpression>(numerator[0]);
            numerator = realYou->getNumerator();
        }
        else if (denominator.size() == 0)
        {
            return numerator[0]->add(number);
        }
    }

    double d = 1;
    double e = 1;
    if (number->getName() == "SumExpression")
    {
        return number->add(shared_from_this());
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
            if (numerator.size() == 1 && numberNumerator.size() == 1)
            {
                numerator[0] = numerator[0]->add(numberNumerator[0]);
                return shared_from_this();
            }
            vector< tr1::shared_ptr<AbstractNumber> > mFinal;
            for (int i=0; i<numerator.size(); i++)
            {
                for (int j=0; j<numberNumerator.size(); j++)
                {
                    if (numerator[i]->getName() != "Exponent" && numberNumerator[j]->getName() != "Exponent")
                    {
                        if (numberNumerator[j]->toDouble() != 0 && numerator[i]->toDouble() != 0)
                        {

                        tr1::shared_ptr<AbstractNumber> tmpDivide = numerator[i]->divide(numberNumerator[j]);
                        if (tmpDivide->getName() != "MultExpression" && tmpDivide->getName() != "SumExpression")
                        {
                            mFinal.push_back(numberNumerator[j]);
                            tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
                            numberNumerator[j] = one;
                            numerator[i] = tmpDivide;
                        }

                        else
                        {
                            tr1::shared_ptr<AbstractNumber> tmpDivide2 = numberNumerator[j]->divide(numerator[i]);
                            if (tmpDivide2->getName() != "MultExpression" && tmpDivide2->getName() != "SumExpression")
                            {
                                mFinal.push_back(numerator[i]);
                                tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
                                numberNumerator[j] = tmpDivide2;
                                numerator[i] = one;
                            }
                        }
                        }
                    }

                }
            }
            if (mFinal.size() == 0)
            {
                vector< tr1::shared_ptr<AbstractNumber> > s;
                s.push_back(shared_from_this());
                s.push_back(number);
                return tr1::shared_ptr<AbstractNumber>(new SumExpression(s));
            }
            numberNumerator = simplifyVector(numberNumerator);
            numerator = simplifyVector(numerator);
            vector< tr1::shared_ptr<AbstractNumber> > sumFinal;
            sumFinal.push_back(numberNumerator[0]);
            sumFinal.push_back(numerator[0]);
            double test = sumFinal[0]->toDouble() + sumFinal[1]->toDouble();
            if (test == round(test))
            {
                tr1::shared_ptr<AbstractNumber> int1(new SmartInteger((int)round(test)));
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
            if (abs(numerator[i]->toDouble() - number->toDouble()) < 0.00001)
            {
                tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
                if (numerator.size() == 2)
                {
                    if (numerator[0]->getName() == "Integer" || numerator[1]->getName() == "Integer")
                    {
                        if (numerator[0]->getName() == "Integer")
                            numerator[0] = numerator[0]->add(one);
                        else
                            numerator[1] = numerator[1]->add(one);
                        return shared_from_this();
                    }
                }
                vector<tr1::shared_ptr<AbstractNumber> > newMult;
                vector<tr1::shared_ptr<AbstractNumber> > newSum;
                for (int j=0; j<numerator.size(); j++)
                {
                    if (j != i)
                        newSum.push_back(numerator[j]);
                }
                newSum.push_back(one);
                tr1::shared_ptr<AbstractNumber> s(new SumExpression(newSum));
                newMult.push_back(s);
                newMult.push_back(number);
                tr1::shared_ptr<AbstractNumber> m(new MultExpression(newMult, '+'));
                return m;
            }

        }
    }
    if (number->getName() == "Integer" && denominator.size() == 1 && numerator.size() == 1)
    {
        if (numerator[0]->getName() == "Integer" && denominator[0]->getName() == "Integer")
        {
            return number->add(shared_from_this());
        }
    }
    vector< tr1::shared_ptr<AbstractNumber> > s;
    s.push_back(shared_from_this());
    s.push_back(number);
    return tr1::shared_ptr<AbstractNumber>(new SumExpression(s));
}
tr1::shared_ptr<AbstractNumber> MultExpression::multiply(tr1::shared_ptr<AbstractNumber>number)
{
    if (number->getName() == "SumExpression")
    {
        return number->multiply(shared_from_this());
    }
    if (number->getName() == "Integer" && denominator.size() == 1 && numerator.size() == 1)
    {
        if (denominator[0]->getName() == "Integer" && numerator[0]->getName() == "Integer")
        {
            numerator.push_back(number);
            return shared_from_this()->simplify();
        }
    }
    if (number->getName() == "MultExpression")
    {
        tr1::shared_ptr<MultExpression> numMult = tr1::static_pointer_cast<MultExpression>(number);
        vector<tr1::shared_ptr<AbstractNumber> > numNumerator(numMult->getNumerator());
        vector<tr1::shared_ptr<AbstractNumber> > numDenominator(numMult->getDenominator());

        for (int i=0; i<numerator.size(); i++)
            numNumerator.push_back(numerator[i]);
        for (int i=0; i<denominator.size(); i++)
            numDenominator.push_back(denominator[i]);
        numNumerator = simplifyVector(numNumerator);
        numDenominator = simplifyVector(numDenominator);
        tr1::shared_ptr<AbstractNumber> me(new MultExpression(numNumerator, numDenominator, '+'));

        return me;
    }

    tr1::shared_ptr<AbstractNumber> tmp;
    for (int i=0; (unsigned)i < denominator.size(); i++)
    {
        if (denominator[i]->toDouble() == number->toDouble())
        {
            denominator.erase(denominator.begin() + i);
            return shared_from_this();
        }
    }
    vector< tr1::shared_ptr<AbstractNumber> > MultTerms = numerator;
    MultTerms.push_back(number->simplify());
    for (int i=0; (unsigned)i < MultTerms.size() - 1; i++)
    {
        if (MultTerms[i]->getName() == MultTerms[MultTerms.size() - 1]->getName())
        {
            if (MultTerms[i]->getName() != "MultExpression" )
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
	return finalMult;
}

tr1::shared_ptr<AbstractNumber> MultExpression::divide(tr1::shared_ptr<AbstractNumber> number){

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

  	if (toDouble() < 0)
  	{
  		output+='-';
  	}

	for (int i =0; i < numerator.size(); i++){
        if (numerator[i]->toDouble() == 0)
        {
            hasZero = true;
            break;
        }
        /*if (i = 0)
        {
        	 output += numerator[swap]->toString();
        	 if (i < numerator.size()-1)
        	 {
        	 	output += "*";
        	 }
        }
        else if(i = swap)
        {
        	 output += numerator[0]->toString();
			 if (i < numerator.size()-1)
			 {
				output += "*";
			 }
        }(*/
       if (numerator[i]->toDouble() != 1 || numerator.size() == 1)
       {
 			output += numerator[i]->noSign()->toString();
 			if (i < numerator.size()-1)
 			{
 				output += "*";
 			}
         }
	}
	for (int i = 0; i < denominator.size(); i++){
		output += "/";
		output += denominator[i]->noSign()->toString();
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
    if (sign == '-')
    {
        sign = '+';
        tr1::shared_ptr<AbstractNumber> nOne = tr1::shared_ptr<AbstractNumber>(new SmartInteger(-1));
        numerator.push_back(nOne);
    }
    tr1::shared_ptr<AbstractNumber> tmp;
    if (denominator.size() > 0)
    {
    	string DBZ = " ";
        for (int i=0; i < denominator.size(); i++)
        {
            if (denominator[i]->toDouble() == 0)
            {
                const char* msg = ("tried to divide by zero");
                throw NumException(msg);
            }
        }
    }
    if (toDouble() == round(toDouble()))
    {
        return tr1::shared_ptr<AbstractNumber>(new SmartInteger(toDouble()));
    }
    numerator = simplifyVector(numerator);
    denominator = simplifyVector(denominator);
    if (denominator.size() == 1)
    {
        if (denominator[0]->getName() == "MultExpression")
        {
            tr1::shared_ptr<MultExpression> tmp = tr1::static_pointer_cast<MultExpression>(denominator[0]);
            denominator = tmp->getNumerator();
            vector<tr1::shared_ptr<AbstractNumber> > tmpNum = tmp->getNumerator();
            for (int i=0; i<tmpNum.size(); i++)
            {
                numerator.push_back(tmpNum[i]);
            }

        }
    }
    if (numerator[0]->getName() == "MultExpression")
    {
        tr1::shared_ptr<MultExpression> tmp = tr1::static_pointer_cast<MultExpression>(numerator[0]);
        numerator = tmp->getNumerator();
        vector<tr1::shared_ptr<AbstractNumber> > tmpDem = tmp->getDenominator();
        for (int i=0; i<tmpDem.size(); i++)
        {
            denominator.push_back(tmpDem[i]);
        }

    }
    if (denominator.size() != 0)
    {
        if (!(denominator.size() == 1 && denominator[0]->getName() == "MultExpression"))
        {
            tmp = numerator[0]->divide(denominator[0]);

            if (tmp->getName() != "MultExpression")
            {
                numerator[0] = tmp;
                denominator.erase(denominator.begin());
            }
            else
            {
                tr1::shared_ptr<MultExpression> tmpMult = tr1::static_pointer_cast<MultExpression>(tmp);
                vector <tr1::shared_ptr<AbstractNumber> > tmpNumerator = tmpMult->getNumerator();
                vector <tr1::shared_ptr<AbstractNumber> > tmpDenominator = tmpMult->getDenominator();

                numerator = tmpNumerator;
                denominator = tmpDenominator;
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

    while (vec.size() > 1)
    {
        vec[0] = vec[0]->multiply(vec[1]);
        vec.erase(vec.begin() + 1);
    }

  //  tr1::shared_ptr<AbstractNumber> minus_one(new SmartInteger(-1));
   // vec[0] = vec[0]->multiply(minus_one);

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
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1 , input.size() - findOutside(':', input)) , false));

		express.push_back(tr1::shared_ptr<AbstractNumber>(new Log(base, value)));

	}
	else if (input[0] == 'l' && input[1] == 'n' && input[2] == ':')
	{
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1 , input.size()), false));
		tr1::shared_ptr<AbstractNumber> base(new E());
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Log(base, value)));
	}
	else if (input[0] == 'l' && input[1] == 'o' && input[2] == 'g' && input[3] == ':')
	{
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1 , input.size()), false));
		tr1::shared_ptr<AbstractNumber> base(new SmartInteger(10));
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Log(base, value)));
	}
	else if (input[0] == 's' && input[1] == 'q' && input[2] == 'r' && input[3] == 't' && input[4] == ':')
	{
		tr1::shared_ptr<AbstractNumber> value(new SumExpression( input.substr( findOutside(':', input) + 1, input.size()) , false));
		tr1::shared_ptr<AbstractNumber> root(new SmartInteger("2"));
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Radical(value, root)));
	}
	else if(input[findOutside('r', input)+1] == 't' && input[findOutside('r', input)+2] == ':'){

		tr1::shared_ptr<AbstractNumber> root(new SumExpression(input.substr(0 , findOutside('r', input)) , false));
		tr1::shared_ptr<AbstractNumber> value(new SumExpression(input.substr(findOutside(':', input)+1, input.size()) , false));

		express.push_back(tr1::shared_ptr<AbstractNumber>(new Radical(value, root)));
	}
	else if (findOutside('^', input) != string::npos)
	{
		tr1::shared_ptr<AbstractNumber> base(new SumExpression(input.substr(0 , findOutside('^', input)) , false));
		tr1::shared_ptr<AbstractNumber> value(new SumExpression(input.substr(findOutside('^', input)+1, input.size()) , false));
		express.push_back(tr1::shared_ptr<AbstractNumber>(new Exponent(base, value)));

	}
	else if (input[0] == 'a' && input[1] == 'n' && input[2] == 's' && input.size() == 3)
	{
		string noAns = " ";
		if (history == "")
		{
			const char* msg = ( "No previous answer found");
            throw NumException(msg);
		}
		express.push_back(tr1::shared_ptr<AbstractNumber>(new SumExpression(history)));
	}
	else if (input[0] == '(' && input[input.size()-1] ==')')
	{
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
		express.push_back(tr1::shared_ptr<AbstractNumber>(new SmartInteger(input)));
	}
	else
	{
	    const char* msg = ( " is not a valid expression; Try removing the spaces.");
        throw NumException(msg);
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

    const char* msg = ("tried to get" + name + "from a multE").c_str();
}
tr1::shared_ptr<AbstractNumber> MultExpression::noSign()
{
	tr1::shared_ptr<AbstractNumber> output(new MultExpression(numerator, denominator, '+'));
	return output;
}

