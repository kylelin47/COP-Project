#include "Log.h"
#include "Exponent.h"
#include "Radical.h"
#include "E.h"
#include "Pi.h"
#include <cmath>

Log::Log(tr1::shared_ptr<AbstractNumber>base, tr1::shared_ptr<AbstractNumber>value)
{
    if (value->toDouble() <= 0)
    {
        throw "Can't take log of a negative number";
    }
    if (base->toDouble() == 1 || base->toDouble() <= 0)
    {
    	throw "Invalid log base";
    }
    this->base = base;
    this->value = value;
    this->sign = '+';
}

Log::Log(tr1::shared_ptr<AbstractNumber>base, tr1::shared_ptr<AbstractNumber>value,char sign)
{
    if (value->toDouble() <= 0)
    {
        throw "Can't take log of a negative number";
    }
    if (base->toDouble() == 1 || base->toDouble() <= 0)
    {
    	throw "Invalid log base";
    }
    this->base = base;
    this->value = value;
    this->sign = sign;
}

 tr1::shared_ptr<AbstractNumber>  Log::add(tr1::shared_ptr<AbstractNumber>number){
	if (number->getName() == "Log" && abs(toDouble() - number->toDouble()) < 0.000001)
	{
		std::vector< tr1::shared_ptr<AbstractNumber> > OutVector;
		tr1::shared_ptr<AbstractNumber> two(new SmartInteger(2));
		tr1::shared_ptr<AbstractNumber> log(new Log(base, value)); // this gets rid of the old sign just in case
		OutVector.push_back(two);
		OutVector.push_back(log);
		if (number->getSign() == getSign())
		{
			tr1::shared_ptr<AbstractNumber> output(new MultExpression(OutVector, getSign()));
			return output;
		}
		else{
			tr1::shared_ptr<AbstractNumber> output(new SmartInteger(0));
			return output;
		}



	}
	else if (number->getName() == "MultExpression" || number->getName() == "SumExpression")
    {
        return number->add(shared_from_this());
    }
	else {
		std::vector< tr1::shared_ptr<AbstractNumber> > OutVector;
		OutVector.push_back(shared_from_this());
		OutVector.push_back(number);
		tr1::shared_ptr<AbstractNumber>output(new SumExpression(OutVector));
		return output;
	}

}
 tr1::shared_ptr<AbstractNumber>  Log::multiply(tr1::shared_ptr<AbstractNumber>number){
	 char sign;
	 if (getSign() == number->getSign())
	 {
		 sign = '+';
	 }
	 else
	 {
		 sign = '-';
	 }
	 tr1::shared_ptr<AbstractNumber> copy(noSign());
	 tr1::shared_ptr<AbstractNumber> num(number->noSign());

	 if (number->getName() == "Log" &&  abs(toDouble() - number->toDouble()) < 0.000001)
	 {
		 tr1::shared_ptr<AbstractNumber> two(new SmartInteger(2));
		 tr1::shared_ptr<AbstractNumber> output(new Exponent(copy, two, sign));
		 return output;
	 }
	 else if (number->getName() == "Exponent") {
		 if (abs(number->getValue("base")->toDouble() - toDouble()) < 0.000001 )
		 {
			 std::vector< tr1::shared_ptr<AbstractNumber> > SumVector;
			 tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
			 SumVector.push_back(one);
			 SumVector.push_back(number->getValue("power"));
			 tr1::shared_ptr<AbstractNumber> power(new SumExpression(SumVector));
			 tr1::shared_ptr<AbstractNumber> output(new Exponent(copy, power, sign));
			 return output;
		 }
	 }
     else if (number->getName() == "MultExpression")
     {
         return number->multiply(shared_from_this());
     }
	 std::vector< tr1::shared_ptr<AbstractNumber> > MultVector;
	 MultVector.push_back(copy);
	 MultVector.push_back(num);

	 tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector, sign));
	 return r;
}
 tr1::shared_ptr<AbstractNumber>  Log::divide(tr1::shared_ptr<AbstractNumber>number){
	 char sign;
	 if (getSign() == number->getSign())
	 {
		 sign = '+';
	 }
	 else
	 {
		 sign = '-';
	 }
	 tr1::shared_ptr<AbstractNumber> copy(new Log(base, value, '+'));
	 tr1::shared_ptr<AbstractNumber> num(number->noSign());

	 if (number->getName() == "Log" &&  abs(toDouble() - number->toDouble()) < 0.000001)
	 {
		 tr1::shared_ptr<AbstractNumber> output(new SmartInteger(1));
		 return output;
	 }
	 else if (number->getName() == "Exponent" && abs(number->getValue("base")->toDouble() - toDouble()) < 0.000001 )
	 {
		 std::vector< tr1::shared_ptr<AbstractNumber> > SumVector;
		 std::vector< tr1::shared_ptr<AbstractNumber> > numer;
		 std::vector< tr1::shared_ptr<AbstractNumber> > den;
		 tr1::shared_ptr<AbstractNumber> negetive_one(new SmartInteger(-1));
		 tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
		 SumVector.push_back(number->getValue("power"));
		 SumVector.push_back(negetive_one);
		 numer.push_back(one);
		 tr1::shared_ptr<AbstractNumber> power(new SumExpression(SumVector));
		 tr1::shared_ptr<AbstractNumber> exponential(new Exponent(copy, power));
		 den.push_back(exponential);
		 tr1::shared_ptr<AbstractNumber> output(new MultExpression(numer, den, sign));

		 return output;
	 }
	 else if (number->getName() == "Radical") {
		 if (abs(number->getValue("value")->toDouble() - toDouble()) < 0.000001 )
		 {
			 std::vector< tr1::shared_ptr<AbstractNumber> > SumVector;
			 tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
			 tr1::shared_ptr<AbstractNumber> invertedRoot(new MultExpression(one, number->getValue("root")->noSign(), number->getValue("root")->getSign()));
			 SumVector.push_back(one);
			 SumVector.push_back(invertedRoot);
			 tr1::shared_ptr<AbstractNumber> power(new SumExpression(SumVector));
			 tr1::shared_ptr<AbstractNumber> output(new Exponent(number->getValue("value")->noSign(), power, sign));
			 return output;
		 }
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
        tr1::shared_ptr<AbstractNumber> reversedMultE(new MultExpression(MultEDem, MultENum, number->getSign()));
        return reversedMultE->multiply(shared_from_this());
     }
	 std::vector< tr1::shared_ptr<AbstractNumber> > numer;
	 std::vector< tr1::shared_ptr<AbstractNumber> > den;
	 numer.push_back(copy);
	 den.push_back(num);

	 tr1::shared_ptr<AbstractNumber> r(new MultExpression(numer, den, sign));
	 return r;
}
string Log::toString(){
	std::stringstream ss;

	if (sign == '-')
	{
		ss << "-";
	}
	ss << "log_";
	ss << base->toString();
	ss << ":";
	ss << value->toString();
	return ss.str();
}

double Log::toDouble()
{
	if (sign == '-')
	{
		return -1*log(value->toDouble())/log(base->toDouble());
	}
	return log(value->toDouble())/log(base->toDouble());
}

 tr1::shared_ptr<AbstractNumber>  Log::simplify()
{
    base = base->simplify();
    value = value->simplify();
    if (abs(toDouble() - round(toDouble())) < 0.00001)
    {
        tr1::shared_ptr<AbstractNumber>n(new SmartInteger((int)round(toDouble())));
        return n;
    }
    if (abs(1/toDouble() - round(1/toDouble())) < 0.000001)
    {
        tr1::shared_ptr<AbstractNumber>n(new SmartInteger(1));
        tr1::shared_ptr<AbstractNumber>n2(new SmartInteger((int)round(1/toDouble())));
        tr1::shared_ptr<AbstractNumber>nF(new MultExpression(n, n2, '+'));
        return nF;
    }
    vector< tr1::shared_ptr<AbstractNumber> > SimplifiedTerms;
    int numOnes = 0;
    if (value->getName() == "Integer")
    {
        vector<int> factors = primeFactors((int)(value->toDouble()));
        if (factors.size() > 1)
        {
            for (int i=0; (unsigned)i < factors.size(); i++)
            {
                if (base->toDouble() == factors[i])
                {
                    numOnes++;
                }
                else
                {
                    if (factors[i] == factors[i + 1])
                    {
                        int sameFactor = 2;
                        for (int k=i+2; (unsigned)k<factors.size(); k++)
                        {
                            if (factors[k] == factors[i])
                            {
                                sameFactor++;
                            }
                            else
                            {
                                break;
                            }

                        }
                        tr1::shared_ptr<AbstractNumber>Coefficient(new SmartInteger(sameFactor));
                        tr1::shared_ptr<AbstractNumber>Int(new SmartInteger(factors[i]));
                        tr1::shared_ptr<AbstractNumber>L(new Log(base, Int));
                        vector<tr1::shared_ptr<AbstractNumber> > M;
                        M.push_back(Coefficient);
                        M.push_back(L);
                        tr1::shared_ptr<AbstractNumber>Mult(new MultExpression(M, '+'));
                        SimplifiedTerms.push_back(Mult);
                        i = i + sameFactor - 1;
                    }
                    else
                    {
                        tr1::shared_ptr<AbstractNumber>Int(new SmartInteger(factors[i]));
                        tr1::shared_ptr<AbstractNumber>L(new Log(base, Int));

                        SimplifiedTerms.push_back(L);
                    }
                }
            }
        }
        else
            return shared_from_this();
    }
    else
    {
        return shared_from_this();
    }
    if (numOnes != 0)
    {
        SimplifiedTerms.push_back(tr1::shared_ptr<AbstractNumber>(new SmartInteger(numOnes)));
    }
    tr1::shared_ptr<AbstractNumber>s(new SumExpression(SimplifiedTerms));

    return s;
}

vector<int> Log::primeFactors(int num)
{
    vector<int> factors;
    for (int i=2; i<=num; i++)
    {
        if (num%i == 0)
        {
            factors.push_back(i);
            num = num/i;
            i = 1;
        }
    }

    if (factors.size() == 0)
    {
        factors.push_back(num);
    }

    return factors;
}

string Log::getName()
{
	return "Log";
}

char Log::getSign(){
	return sign;
}

tr1::shared_ptr<AbstractNumber> Log::getValue(string name){
	if (name == "base") {
		return this->base;
	}
	else if (name == "value")
	{
		return this->value;
	}
	else
	{
		throw "ERROR: tried to get a " + name + " from a log";
	}
}

tr1::shared_ptr<AbstractNumber> Log::removeNegative(tr1::shared_ptr<AbstractNumber>number){
	//*******************************************************
		 //Copy and paste this to git rid of negetives
		 //****************************************************
		 if (number->getName() == "Log")
		 {
			 tr1::shared_ptr<AbstractNumber> num(new Log(number->getValue("base"), number->getValue("value"), '+'));
			 return num;
		 }
		 else if (number->getName() == "Exponent")
		 {
			 tr1::shared_ptr<AbstractNumber> num(new Exponent(number->getValue("base"), number->getValue("power"), '+'));
			 return num;
		 }
		 else if (number->getName() == "Radical")
		 {
		 	tr1::shared_ptr<AbstractNumber> num(new Radical(number->getValue("root"), number->getValue("value"), '+'));
		 	return num;
		 }
		 else if (number->getName() == "E")
		 {
			tr1::shared_ptr<AbstractNumber> num(new E());
			return num;
		 }
		 else if (number->getName() == "Pi")
		 {
			tr1::shared_ptr<AbstractNumber> num(new Pi());
			return num;
		 }
		 else if (number->getName() == "Integer")
		 {
			 tr1::shared_ptr<AbstractNumber> num(new SmartInteger(number->toDouble()));
			 return num;
		 }
		 else
		 {
			 tr1::shared_ptr<AbstractNumber> num(number);
			 return num;
		 }


		 //*************************************************
		 //end
		 //**********************************************
}

tr1::shared_ptr<AbstractNumber> Log::noSign()
{
	tr1::shared_ptr<AbstractNumber> output(new Log(base, value));
	return output;
}
