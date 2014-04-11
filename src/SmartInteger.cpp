/*
 * SmartInteger.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#include "SumExpression.h"
#include <cmath>

using namespace std;

SmartInteger::SmartInteger(int value, char sign) {
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
    vector< tr1::shared_ptr<AbstractNumber> > SumTerms;

    if (number->getName() == "Integer")
    {
        tr1::shared_ptr<AbstractNumber>n(new SmartInteger(this->value + number->toDouble()));
        return n;
    }

    else
    {
        cout << "ADDING LOG" << endl;
        return number->add(shared_from_this());
    }
    tr1::shared_ptr<AbstractNumber>s (new SumExpression(SumTerms));
    return s;
}
tr1::shared_ptr<AbstractNumber> SmartInteger::multiply(tr1::shared_ptr<AbstractNumber>number){
    vector< tr1::shared_ptr<AbstractNumber> > MultipliedTerms;
    number = number->simplify();
    if (number->getName() == "Integer")
    {
        value = this->value * number->toDouble();
        return shared_from_this();
    }
    else
    {
        return number->multiply(shared_from_this());
    }
    /*
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
    MultipliedTerms.push_back(shared_from_this());
    MultipliedTerms.push_back(number);
    tr1::shared_ptr<AbstractNumber>M (new MultExpression(MultipliedTerms, sign));
    return M;
    */
}

tr1::shared_ptr<AbstractNumber> SmartInteger::divide(tr1::shared_ptr<AbstractNumber>number){
    if (number -> getName() == "Integer")
    {

        if((this->value % (int)(number->toDouble())) != 0)
        {
            vector<tr1::shared_ptr<AbstractNumber> > numerator;
            vector<tr1::shared_ptr<AbstractNumber> > denominator;
            tr1::shared_ptr<AbstractNumber> n(new SmartInteger(this->value, '+'));
            tr1::shared_ptr<AbstractNumber> d(new SmartInteger(number->toDouble(), '+'));

            numerator.push_back(n);
            denominator.push_back(d);
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


            tr1::shared_ptr<AbstractNumber> D(new MultExpression(numerator, denominator, sign));
            return D;

        }

        else if((this->value % GCF(this->value, (int)number->toDouble())) != 0)
        {
            vector<tr1::shared_ptr<AbstractNumber> > numerator;
                   vector<tr1::shared_ptr<AbstractNumber> > denominator;
                   tr1::shared_ptr<AbstractNumber> n(new SmartInteger((this->value / GCF(this->value, (int)number->toDouble())),'+'));
                   tr1::shared_ptr<AbstractNumber> d(new SmartInteger((number->toDouble() / GCF(this->value, (int)number->toDouble())), '+'));
                   numerator.push_back(n);
                   denominator.push_back(d);

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

                   tr1::shared_ptr<AbstractNumber> D(new MultExpression(numerator, denominator, sign));
                   return D;
        }

        else
        {
            vector<tr1::shared_ptr<AbstractNumber> > DividedTerms;

            tr1::shared_ptr<AbstractNumber> n(new SmartInteger(this->value / number->toDouble()));
            DividedTerms.push_back(n);

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

            tr1::shared_ptr<AbstractNumber> D(new MultExpression(DividedTerms, sign));
            return D;
        }

    }
    vector<tr1::shared_ptr<AbstractNumber> > numerator;
            vector<tr1::shared_ptr<AbstractNumber> > denominator;
            tr1::shared_ptr<AbstractNumber> n(new SmartInteger(this->value));
            tr1::shared_ptr<AbstractNumber> d(new SmartInteger(number->toDouble()));
            numerator.push_back(n);
            denominator.push_back(d);
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

            tr1::shared_ptr<AbstractNumber> D(new MultExpression(numerator, denominator, sign));
            return D;
}

string SmartInteger::toString(){
	stringstream ss;

	ss << value;
	return ss.str();
}

double SmartInteger::toDouble()
{
	//cout << value;
	return (double)value;
}

tr1::shared_ptr<AbstractNumber> SmartInteger::simplify()
{
    if (sign == '-')
    {
        value = -value;
    }
	return shared_from_this();
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

int SmartInteger::GCF(int x, int y)
{
	        	if (x == 0)
	        	{
	        		return y;
	        	}
	        	else
	        	{
	        		return GCF(x, y % x);
	        	}

}
