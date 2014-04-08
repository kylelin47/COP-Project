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
    static SumExpression S = SumExpression(SumTerms);
    static SmartInteger Int = SmartInteger(0);
    static SmartInteger self = SmartInteger(value);

    if (number->getName() == "Integer")
    {
        Int = SmartInteger(this->value + number->toDouble());
        return &Int;
    }

    else
    {
        self = SmartInteger(value);
        return number->add(&self);
    }
    S = SumExpression(SumTerms);
    return &S;
}
AbstractNumber * SmartInteger::multiply(AbstractNumber *number){
    vector<AbstractNumber*> MultipliedTerms;
    static SmartInteger Int = SmartInteger(0);
    static MultExpression M = MultExpression(MultipliedTerms);

    if (number->getName() == "Integer")
    {
        Int = SmartInteger(this->value * number->toDouble());
        MultipliedTerms.push_back(&Int);
    }

    M = MultExpression(MultipliedTerms);
    return &M;
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
    static SmartInteger Int = SmartInteger(value);
    Int = SmartInteger(value);
	return &Int;
}
string SmartInteger::getName()
{
	return "Integer";
}



