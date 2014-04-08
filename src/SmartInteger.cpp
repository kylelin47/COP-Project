/*
 * SmartInteger.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#include "SmartInteger.h"

using namespace std;

SmartInteger::SmartInteger(int value) {

    this->value = value;
}



SmartInteger::~SmartInteger() {
	// TODO Auto-generated destructor stub
}

AbstractNumber * SmartInteger::add(AbstractNumber *number){
    vector<AbstractNumber*> SumTerms;

    if (number->getName() == "Integer")
    {
        AbstractNumber *n = new SmartInteger(this->value + number->toDouble());
        return n;
    }

    else
    {
        return number->add(this);
    }
    AbstractNumber *s = new SumExpression(SumTerms);
    return s;
}
AbstractNumber * SmartInteger::multiply(AbstractNumber *number){
    vector<AbstractNumber*> MultipliedTerms;

    if (number->getName() == "Integer")
    {
        AbstractNumber *n = new SmartInteger(this->value * number->toDouble());
        MultipliedTerms.push_back(n);
    }

    AbstractNumber *M = new MultExpression(MultipliedTerms);
    return M;
}
AbstractNumber * SmartInteger::divide(AbstractNumber *number){

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

AbstractNumber * SmartInteger::simplify()
{
	return this;
}
string SmartInteger::getName()
{
	return "Integer";
}



