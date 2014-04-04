#include "Pi.h"

Pi::Pi(const string &input)
{
    //ctor
}

Pi::~Pi()
{
    //dtor
}

vector<AbstractNumber*> Pi::add(AbstractNumber *number){

}
vector<AbstractNumber*> Pi::multiply(AbstractNumber *number){

}
vector<AbstractNumber*> Pi::divide(AbstractNumber *number){

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

bool Pi::simplify()
{
	return false;
}
string Pi::getName()
{
	return "Pi";
}
