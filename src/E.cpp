#include "E.h"

E::E(const string &input)
{
    //ctor
}

E::~E()
{
    //dtor
}

tr1::shared_ptr<AbstractNumber> E::add(tr1::shared_ptr<AbstractNumber>number){

}
tr1::shared_ptr<AbstractNumber> E::multiply(tr1::shared_ptr<AbstractNumber>number){

}
tr1::shared_ptr<AbstractNumber> E::divide(tr1::shared_ptr<AbstractNumber>number){

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

tr1::shared_ptr<AbstractNumber> E::simplify()
{
}
string E::getName()
{
	return "E";
}
