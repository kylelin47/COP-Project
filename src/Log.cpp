#include "Log.h"
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

    if (number->getName() == "Log")
    {
        if (base->toDouble() == number->base->toDouble())
        {
            //probably unnecessary
        }
    }
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
    if (abs(remainder(toDouble(), 1)) < pow(10, -6))
    {
        tr1::shared_ptr<AbstractNumber>n(new SmartInteger((int)round(toDouble())));
        return n;
    }

    vector< tr1::shared_ptr<AbstractNumber> > SimplifiedTerms;

    if (value->getName() == "Integer")
    {

        vector<int> factors = primeFactors((int)(value->toDouble()));
        for (int i=0; (unsigned)i < factors.size(); i++)
        {
            tr1::shared_ptr<AbstractNumber>Int(new SmartInteger(factors[i]));
            tr1::shared_ptr<AbstractNumber>L(new Log(base, Int));

            SimplifiedTerms.push_back(L);
        }
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

