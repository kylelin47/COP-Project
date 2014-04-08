#include "Pi.h"

Pi::Pi(const string &input)
{
    //ctor
}

Pi::~Pi()
{
    //dtor
}

AbstractNumber * Pi::add(AbstractNumber *number){

}
AbstractNumber * Pi::multiply(AbstractNumber *number){

}
AbstractNumber * Pi::divide(AbstractNumber *number){

}
string Pi::toString(){
	stringstream ss;

	ss << value;
	return ss.str();
}

double Pi::toDouble()
{
	return 0;
}

AbstractNumber * Pi::simplify()
{
	return false;
}
string Pi::getName()
{
	return "Pi";
}
