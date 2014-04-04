#include "E.h"

E::E(const string &input)
{
    //ctor
}

E::~E()
{
    //dtor
}

vector<AbstractNumber*> E::add(AbstractNumber *number){

}
vector<AbstractNumber*> E::multiply(AbstractNumber *number){

}
vector<AbstractNumber*> E::divide(AbstractNumber *number){

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

bool E::simplify()
{
	return false;
}
string E::getName()
{
	return "E";
}
