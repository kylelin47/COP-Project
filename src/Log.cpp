#include "Log.h"
#include <cmath>

Log::Log(AbstractNumber *base, AbstractNumber *value)
{
    if (value->toDouble() <= 0)
    {
        throw "Can't take log of a negative number";
    }
    this->base = base;
    this->value = value;
}

AbstractNumber* Log::add(AbstractNumber *number){

    std::vector<AbstractNumber*> SumVector;
    SumVector.push_back(this);
    SumVector.push_back(number);
    AbstractNumber *s = new SumExpression(SumVector);

    return s;
}
AbstractNumber* Log::multiply(AbstractNumber *number){

    if (number->getName() == "Log")
    {
        if (base->toDouble() == number->base->toDouble())
        {
            //probably unnecessary
        }
    }
}
AbstractNumber* Log::divide(AbstractNumber *number){

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

AbstractNumber* Log::simplify()
{
    if (abs(remainder(toDouble(), 1)) < pow(10, -6))
    {
        AbstractNumber *n = new SmartInteger((int)round(toDouble()));
        return n;
    }

    vector<AbstractNumber*> SimplifiedTerms;

    if (value->getName() == "Integer")
    {

        vector<int> factors = primeFactors((int)(value->toDouble()));
        for (int i=0; (unsigned)i < factors.size(); i++)
        {
            AbstractNumber *Int = new SmartInteger(factors[i]);
            AbstractNumber *L = new Log(base, Int);
            //delete Int;
            SimplifiedTerms.push_back(L);
        }
    }
    AbstractNumber *s = new SumExpression(SimplifiedTerms);

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

