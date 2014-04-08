#include "E.h"

E::E(const string &input)
{
    //ctor
}

E::~E()
{
    //dtor
}

AbstractNumber * E::add(AbstractNumber *number){

}
AbstractNumber * E::multiply(AbstractNumber *number){

}
AbstractNumber * E::divide(AbstractNumber *number){

}
string E::toString(){
	stringstream ss;

	ss << value;
	return ss.str();
}

double E::toDouble()
{
	return 0;
}

AbstractNumber * E::simplify()
{
}
string E::getName()
{
	return "E";
}
