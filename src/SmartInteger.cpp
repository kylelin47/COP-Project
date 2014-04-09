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

SmartInteger::SmartInteger(const string &input) {

	stringstream ss(input);

	ss >> value;

}

SmartInteger::~SmartInteger() {
	this->delete;
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
        return number->add(shared_from_this());
    }
    tr1::shared_ptr<AbstractNumber>s(new SumExpression(SumTerms));
    return s;
}
tr1::shared_ptr<AbstractNumber> SmartInteger::multiply(tr1::shared_ptr<AbstractNumber>number){
    vector< tr1::shared_ptr<AbstractNumber> > MultipliedTerms;

    if (number->getName() == "Integer")
    {
        tr1::shared_ptr<AbstractNumber>n(new SmartInteger(this->value * number->toDouble()));
        MultipliedTerms.push_back(n);
    }

    tr1::shared_ptr<AbstractNumber>M (new MultExpression(MultipliedTerms));
    return M;
}
tr1::shared_ptr<AbstractNumber> SmartInteger::divide(tr1::shared_ptr<AbstractNumber>number){

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

tr1::shared_ptr<AbstractNumber> SmartInteger::simplify()
{
	return shared_from_this();
}
string SmartInteger::getName()
{
	return "Integer";
}

char SmartInteger::getSign()
{
	return '+';
}
