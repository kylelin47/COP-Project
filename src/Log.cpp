#include "Log.h"
#include <cmath>

Log::Log(AbstractNumber *base, AbstractNumber *value)
{
    this->base = base;
    this->value = value;
}

std::vector<AbstractNumber*> Log::add(AbstractNumber *number){

    std::vector<AbstractNumber*> SumVector;
    SumVector.push_back(this);
    SumVector.push_back(number);
    return SumVector;
}
std::vector<AbstractNumber*> Log::multiply(AbstractNumber *number){

    if (number->getName() == "Log")
    {
        if (base->toDouble() == number->base->toDouble())
        {
            //probably unnecessary
        }
    }
}
std::vector<AbstractNumber*> Log::divide(AbstractNumber *number){

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

bool Log::simplify()
{
    if (abs(log(value->toDouble())/log(base->toDouble())) < pow(10, -6))
    {
        return true;
    }
	return false;
}
string Log::getName()
{
	return "Log";
}

