#include "Pi.h"

Pi::Pi()
{
    //ctor
}

Pi::~Pi()
{
    //dtor
}

tr1::shared_ptr<AbstractNumber> Pi::add(tr1::shared_ptr<AbstractNumber>number){

}
tr1::shared_ptr<AbstractNumber> Pi::multiply(tr1::shared_ptr<AbstractNumber>number){

}
tr1::shared_ptr<AbstractNumber> Pi::divide(tr1::shared_ptr<AbstractNumber>number){

}
string Pi::toString(){
	return "pi";
}

double Pi::toDouble()
{
	return 0;
}

tr1::shared_ptr<AbstractNumber> Pi::simplify()
{
	return shared_from_this();
}
string Pi::getName()
{
	return "Pi";
}

char Pi::getSign()
{
	return '+';
}
