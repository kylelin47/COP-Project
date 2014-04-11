#include "Pi.h"

Pi::Pi()
{
    this->sign = '+';
}

Pi::Pi(char sign)
{
    this->sign = sign;
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
	if (sign == '-')
	{
		return "-pi";
	}
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
	return sign;
}

tr1::shared_ptr<AbstractNumber> Pi::getValue(string name){

	throw "tried to get a " + name + " from a pi";

}

tr1::shared_ptr<AbstractNumber> Pi::noSign()
{
	tr1::shared_ptr<AbstractNumber> output(new Pi());
	return output;
}
