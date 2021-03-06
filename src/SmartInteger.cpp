/*
 * SmartInteger.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#include "SumExpression.h"
#include <cmath>

using namespace std;

/*SmartInteger::SmartInteger(int value, char sign)
{
	this->value = value;
	this->sign = sign;

}*/

SmartInteger::SmartInteger(int value) {

	this->value = value;
    this->sign = '+';
}


SmartInteger::SmartInteger(const string &input) {

	stringstream ss(input);
	ss >> value;
    this->sign = '+';
}

SmartInteger::~SmartInteger() {
	//this->delete;
}

tr1::shared_ptr<AbstractNumber> SmartInteger::add(tr1::shared_ptr<AbstractNumber>number){
    if (number->getName() == "MultExpression")
    {
        tr1::shared_ptr<MultExpression> tmpMult = tr1::static_pointer_cast<MultExpression>(number);
        vector < tr1::shared_ptr<AbstractNumber> > numberNumerator = tmpMult->getNumerator();
        vector < tr1::shared_ptr<AbstractNumber> > numberDenominator = tmpMult->getDenominator();
        if (numberNumerator[0]->getName() == "Integer" &&
            numberNumerator.size() == 1 && numberDenominator.size() == 1)
        {
            if (numberDenominator[0]->getName() == "Integer")
            {

            int num1 = (int)numberNumerator[0]->toDouble();
            int denom = (int)numberDenominator[0]->toDouble();

            int num2 = this->value * denom;

            int num3 = num2 + num1;

            int commonFactor = GCF(num3, denom);
            if(num3 % commonFactor == 0)
            {
                tr1::shared_ptr<AbstractNumber> n(new SmartInteger((num3 / commonFactor)));
                tr1::shared_ptr<AbstractNumber> d(new SmartInteger((denom / commonFactor)));

                tr1::shared_ptr<AbstractNumber> A(new MultExpression(n, d, '+'));
                return A;
            }
            else
            {
                tr1::shared_ptr<AbstractNumber> n(new SmartInteger(num3));
                tr1::shared_ptr<AbstractNumber> d(new SmartInteger(denom));

                tr1::shared_ptr<AbstractNumber> A(new MultExpression(n, d, '+'));
                return A;

            }

            }
            else
            {
            return number->add(shared_from_this());
            }
        }
        else
        {
            return number->add(shared_from_this());
        }
    }
    else if (number->getName() == "Integer")
    {
        tr1::shared_ptr<AbstractNumber>n(new SmartInteger(this->value + number->toDouble()));
        return n;
    }

    else if (number->getName() == "SumExpression" || number->getName() == "MultExpression")
    {
        return number->add(shared_from_this());
    }
    tr1::shared_ptr<AbstractNumber>s (new SumExpression(shared_from_this(), number));
    return s;
}
tr1::shared_ptr<AbstractNumber> SmartInteger::multiply(tr1::shared_ptr<AbstractNumber>number){

	tr1::shared_ptr<AbstractNumber> copy(shared_from_this());
    if (number->getName() == "Integer")
    {
        tr1::shared_ptr<AbstractNumber> newValue(new SmartInteger(this->value * number->toDouble()));
        return newValue;
    }
    else if (number->getName() == "SumExpression" || number->getName() == "MultExpression")
    {
        return number->multiply(shared_from_this());
    }
    vector<tr1::shared_ptr<AbstractNumber> > M;
    M.push_back(number);
    M.push_back(copy);
    tr1::shared_ptr<AbstractNumber> ans(new MultExpression(M, '+'));
    return ans;
}

tr1::shared_ptr<AbstractNumber> SmartInteger::divide(tr1::shared_ptr<AbstractNumber>number){

    if (number -> getName() == "Integer")
    {
        if (number->toDouble() == 0)
        {
            throw NumException((const char*)"Tried to divide by zero. Our bad!");
        }

        if((this->value % (int)(number->toDouble())) != 0)
        {
        	int commonFactor = GCF((int)this->toDouble(), (int)number->toDouble());
        	if(this->value % commonFactor == 0)
        	{
        	   vector<tr1::shared_ptr<AbstractNumber> > numerator;
			   vector<tr1::shared_ptr<AbstractNumber> > denominator;
			   tr1::shared_ptr<AbstractNumber> n(new SmartInteger((this->toDouble() / commonFactor)));
			   tr1::shared_ptr<AbstractNumber> d(new SmartInteger((number->toDouble() / commonFactor)));
			   numerator.push_back(n);
			   denominator.push_back(d);



			   tr1::shared_ptr<AbstractNumber> D(new MultExpression(numerator, denominator, '+'));
			   return D;
        	}

        	else
        	{
				vector<tr1::shared_ptr<AbstractNumber> > numerator;
				vector<tr1::shared_ptr<AbstractNumber> > denominator;
				tr1::shared_ptr<AbstractNumber> n(new SmartInteger(this->toDouble()));
				tr1::shared_ptr<AbstractNumber> d(new SmartInteger(number->toDouble()));

				numerator.push_back(n);
				denominator.push_back(d);



				tr1::shared_ptr<AbstractNumber> D(new MultExpression(numerator, denominator, '+'));
				return D;
        	}

        }

        vector<tr1::shared_ptr<AbstractNumber> > DividedTerms;

        tr1::shared_ptr<AbstractNumber> n(new SmartInteger(this->toDouble() / number->toDouble()));
        DividedTerms.push_back(n);
        tr1::shared_ptr<AbstractNumber> D(new MultExpression(DividedTerms, '+'));
        return D;

    }
    else if(number->getName() == "MultExpression")
    {
        tr1::shared_ptr<MultExpression> MultE = tr1::static_pointer_cast<MultExpression>(number);
        vector<tr1::shared_ptr<AbstractNumber> > MultENum = MultE->getNumerator();
        vector<tr1::shared_ptr<AbstractNumber> > MultEDem = MultE->getDenominator();
        if (MultEDem.size() == 0)
        {
            tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
            MultEDem.push_back(one);
        }
        tr1::shared_ptr<AbstractNumber> reversedMultE(new MultExpression(MultEDem, MultENum, '+'));
        return reversedMultE->multiply(shared_from_this());
    }
    vector<tr1::shared_ptr<AbstractNumber> > numerator;
	vector<tr1::shared_ptr<AbstractNumber> > denominator;
	tr1::shared_ptr<AbstractNumber> n(new SmartInteger(this->toDouble()));
	numerator.push_back(n);
	denominator.push_back(number);

	tr1::shared_ptr<AbstractNumber> D(new MultExpression(numerator, denominator, '+'));
	return D;
}
string SmartInteger::toString(){
	stringstream ss;
	ss << value;
	return ss.str();
}

double SmartInteger::toDouble()
{
	return (double)value;
}

tr1::shared_ptr<AbstractNumber> SmartInteger::simplify()
{
    tr1::shared_ptr<AbstractNumber> output(new SmartInteger(value));
	return output;
}
string SmartInteger::getName()
{
	return "Integer";
}

char SmartInteger::getSign()
{
	return sign;
}

tr1::shared_ptr<AbstractNumber> SmartInteger::getValue(string name){
//
	const char* msg = ("tried to get" + name + "from an integer").c_str();
	throw NumException(msg);

}

tr1::shared_ptr<AbstractNumber> SmartInteger::noSign()
{
	tr1::shared_ptr<AbstractNumber> output(new SmartInteger(abs(toDouble())));
	return output;
}
int SmartInteger::GCF(int x, int y)
{

	int  gcd;
	for(int i=1;i<=x && i<=y ;i++){


	     if(x%i==0 && y%i == 0 ){

	      gcd=i;

	   }

	}
	return gcd;

}
