#include "E.h"

E::E()
{
    this->sign = '+';
}

E::E(char sign)
{
    this->sign = sign;
}

E::~E()
{
    //dtor
}

tr1::shared_ptr<AbstractNumber> E::getValue(string name){
	throw "tried to get" + name + "from an E()";
}

tr1::shared_ptr<AbstractNumber> E::add(tr1::shared_ptr<AbstractNumber>number){

}
tr1::shared_ptr<AbstractNumber> E::multiply(tr1::shared_ptr<AbstractNumber>number){

}
tr1::shared_ptr<AbstractNumber> E::divide(tr1::shared_ptr<AbstractNumber>number){

}
string E::toString(){
	if (sign == '-')
	{
		return "-e";
	}
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
	return sign;
}

tr1::shared_ptr<AbstractNumber> E::noSign()
{
	tr1::shared_ptr<AbstractNumber> output(new E());
	return output;
}
