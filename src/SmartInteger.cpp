/*
 * SmartInteger.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#include "SumExpression.h"
#include <cmath>

using namespace std;

SmartInteger::SmartInteger(int value, char sign)
{

	this->value = value;
	this->sign = sign;

}

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
    if (number->getName() == "Integer")
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
	char sign;
	if(getSign() == number->getSign())
	{
		sign = '+';
	}
	else{
		sign = '-';
	}
	tr1::shared_ptr<AbstractNumber> copy(noSign());
	tr1::shared_ptr<AbstractNumber> that(number->noSign());
    //number = number->simplify();
    if (number->getName() == "Integer")
    {
        tr1::shared_ptr<AbstractNumber> newValue(new SmartInteger(this->value * number->toDouble())); //this may be bad, check here if we are having issues
        return newValue;
    }
    else if (number->getName() == "SumExpression" || number->getName() == "MultExpression")
    {
        return number->multiply(shared_from_this());
    }
    vector<tr1::shared_ptr<AbstractNumber> > M;
    M.push_back(that);
    M.push_back(copy);
    tr1::shared_ptr<AbstractNumber> ans(new MultExpression(M, sign));
    return ans;
}

tr1::shared_ptr<AbstractNumber> SmartInteger::divide(tr1::shared_ptr<AbstractNumber>number){
	char sign;
	if(this->getSign() == '+' && number->getSign() == '+')
	   {
		sign = '+';
	   }
	else if(this->getSign() == '-' && number->getSign() == '-')
	   {
		sign = '+';
	   }
	else
	   {
		sign = '-';
	   }

    if (number -> getName() == "Integer")
    {

        if((this->value % (int)(number->toDouble())) != 0)
        {
        	int commonFactor = GCF((int)this->noSign()->toDouble(), (int)number->noSign()->toDouble());
        	if(this->value % commonFactor == 0)
        	{
        	   vector<tr1::shared_ptr<AbstractNumber> > numerator;
			   vector<tr1::shared_ptr<AbstractNumber> > denominator;
			   tr1::shared_ptr<AbstractNumber> n(new SmartInteger((this->noSign()->toDouble() / commonFactor)));
			   tr1::shared_ptr<AbstractNumber> d(new SmartInteger((number->noSign()->toDouble() / commonFactor)));
			   numerator.push_back(n);
			   denominator.push_back(d);



			   tr1::shared_ptr<AbstractNumber> D(new MultExpression(numerator, denominator, sign));
			   return D;
        	}

        	else
        	{
				vector<tr1::shared_ptr<AbstractNumber> > numerator;
				vector<tr1::shared_ptr<AbstractNumber> > denominator;
				tr1::shared_ptr<AbstractNumber> n(new SmartInteger(this->noSign()->toDouble(), '+'));
				tr1::shared_ptr<AbstractNumber> d(new SmartInteger(number->noSign()->toDouble(), '+'));

				numerator.push_back(n);
				denominator.push_back(d);



				tr1::shared_ptr<AbstractNumber> D(new MultExpression(numerator, denominator, sign));
				return D;
        	}

        }



        else
        {
            vector<tr1::shared_ptr<AbstractNumber> > DividedTerms;

            tr1::shared_ptr<AbstractNumber> n(new SmartInteger(this->noSign()->toDouble() / number->noSign()->toDouble()));
            DividedTerms.push_back(n);
            tr1::shared_ptr<AbstractNumber> D(new MultExpression(DividedTerms, sign));
            return D;
        }

    }
    vector<tr1::shared_ptr<AbstractNumber> > numerator;
	vector<tr1::shared_ptr<AbstractNumber> > denominator;
	tr1::shared_ptr<AbstractNumber> n(new SmartInteger(this->noSign()->toDouble()));
	numerator.push_back(n);
	denominator.push_back(number->noSign());

	tr1::shared_ptr<AbstractNumber> D(new MultExpression(numerator, denominator, sign));
	return D;
}
string SmartInteger::toString(){
	stringstream ss;
	if (sign == '-' && value < 0)
	{
		ss<< -value;
	}
	else if (sign == '+' && value < 0)
	{
		ss << '-';
		ss<< -value;
	}
	else if (sign == '-' && value > 0)
	{
		ss << '-';
		ss << value;
	}
	else
	{
		ss << value;
	}
	return ss.str();
}

double SmartInteger::toDouble()
{
	//cout << value;
	if (sign == '-')
	{
			return -1*(double)value;
	}
	return (double)value;
}

tr1::shared_ptr<AbstractNumber> SmartInteger::simplify()
{
	int outValue = value;
    if (sign == '-')
    {
        outValue = -value;

    }
    tr1::shared_ptr<AbstractNumber> output(new SmartInteger(outValue));
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


	throw "tried to get a " + name + " from a SmartInteger";

}

tr1::shared_ptr<AbstractNumber> SmartInteger::noSign()
{
	if (sign == '+')
	{
		tr1::shared_ptr<AbstractNumber> output(new SmartInteger(toDouble()));
		return output;
	}
	else
	{
		tr1::shared_ptr<AbstractNumber> output(new SmartInteger(-1*toDouble()));
		return output;
	}


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
