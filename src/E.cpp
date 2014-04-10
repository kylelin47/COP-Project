#include "E.h"

E::E()
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
	return "e";
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

char E::getSign()
{
	return '+';
}
