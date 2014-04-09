#include "Pi.h"

Pi::Pi()
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
	return "pi";
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

char Pi::getSign()
{
	return '+';
}
