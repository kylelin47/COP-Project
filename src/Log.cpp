#include "Log.h"
#include "Exponent.h"
#include <cmath>

Log::Log(tr1::shared_ptr<AbstractNumber>base, tr1::shared_ptr<AbstractNumber>value)
{
    if (value->toDouble() <= 0)
    {
        throw "Can't take log of a negative number";
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
    this->base = base;
    this->value = value;
    this->sign = sign;
}

 tr1::shared_ptr<AbstractNumber>  Log::add(tr1::shared_ptr<AbstractNumber>number){
	if (number->getName() == "Log" && toDouble() == number->toDouble())
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



	 if (number->getName() == "Log" &&  toDouble() == number->toDouble())
	 {
		 tr1::shared_ptr<AbstractNumber> two(new SmartInteger(2));
		 tr1::shared_ptr<AbstractNumber> output(new Exponent(shared_from_this(), two, sign));
		 return output;
	 }
	 else if (number->getName() == "Exponent" && number->getValue("base")->toDouble() == toDouble() )
	 {
		 std::vector< tr1::shared_ptr<AbstractNumber> > SumVector;
		 tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
		 SumVector.push_back(one);
		 SumVector.push_back(number->getValue("power"));
		 tr1::shared_ptr<AbstractNumber> power(new SumExpression(SumVector));
		 tr1::shared_ptr<AbstractNumber> output(new Exponent(shared_from_this(), power, sign));
		 return output;
	 }
	 std::vector< tr1::shared_ptr<AbstractNumber> > MultVector;
	 MultVector.push_back(shared_from_this());
	 MultVector.push_back(number);
	 tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector, '+'));
	 return r;
}
 tr1::shared_ptr<AbstractNumber>  Log::divide(tr1::shared_ptr<AbstractNumber>number){

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
	return log(value->toDouble())/log(base->toDouble());
}

 tr1::shared_ptr<AbstractNumber>  Log::simplify()
{
    base = base->simplify();
    value = value->simplify();
    if (abs(remainder(toDouble(), 1)) < pow(10, -6))
    {
        tr1::shared_ptr<AbstractNumber>n(new SmartInteger((int)round(toDouble())));
        return n;
    }

    vector< tr1::shared_ptr<AbstractNumber> > SimplifiedTerms;
    int numOnes = 0;
    if (value->getName() == "Integer")
    {
        vector<int> factors = primeFactors((int)(value->toDouble()));
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
                    for (int k=i+2; k<factors.size(); k++)
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
		cout << "ERROR";
		throw "tried to get a " + name + " from a log";
	}
}
