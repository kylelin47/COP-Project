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
    static SumExpression s = SumExpression(SumVector);
    s = SumExpression(SumVector);
    return &s;
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
        static SmartInteger Int = SmartInteger((int)round(toDouble()));
        return &Int;
    }

    static Log L = Log(base, value);
    vector<AbstractNumber*> SimplifiedTerms;

    if (value->getName() == "Integer")
    {
        static SmartInteger Int = SmartInteger(0);

        vector<int> factors = primeFactors((int)(value->toDouble()));
        for (int i=0; (unsigned)i < factors.size(); i++)
        {
            Int = SmartInteger(factors[i]);
            L = Log(base, &Int);
            SimplifiedTerms.push_back(&L);
        }
    }
    static SumExpression s = SumExpression(SimplifiedTerms);
    s = SumExpression(SimplifiedTerms);

    return &s;
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

