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
}

 tr1::shared_ptr<AbstractNumber>  Log::add(tr1::shared_ptr<AbstractNumber>number){

    std::vector< tr1::shared_ptr<AbstractNumber> > SumVector;
    SumVector.push_back(shared_from_this());
    SumVector.push_back(number);
    tr1::shared_ptr<AbstractNumber>s(new SumExpression(SumVector));

    return s;
}
 tr1::shared_ptr<AbstractNumber>  Log::multiply(tr1::shared_ptr<AbstractNumber>number){

    if (number->getName() == "Log")
    {
        if (base->toDouble() == number->base->toDouble())
        {
            //probably unnecessary
        }
    }
	std::vector< tr1::shared_ptr<AbstractNumber> > MultVector;
	MultVector.push_back(shared_from_this());
	MultVector.push_back(number);
	tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector, '+'));
	return r;
}
 tr1::shared_ptr<AbstractNumber>  Log::divide(tr1::shared_ptr<AbstractNumber>number){
	// Changes number to exponent with power of -1 then multiplies inverted number
	//tr1::shared_ptr<AbstractNumber> i(new SmartInteger(-1));
	//tr1::shared_ptr<AbstractNumber> r(new Exponent(number, i));
	//return multiply(r);
}
string Log::toString(){
	std::stringstream ss;

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

 tr1::shared_ptr<AbstractNumber> Log::simplify()
{
    base = base->simplify();
    value = value->simplify();

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

            SimplifiedTerms.push_back(L);d
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
	return '+';
}

