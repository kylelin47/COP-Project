#include "Radical.h"

Radical::Radical( tr1::shared_ptr<AbstractNumber>  value,  tr1::shared_ptr<AbstractNumber>  root)
{
    this->value = value;
    this->root = root;
    this->sign = '+';
    checkValidity(value, root);
}

Radical::Radical( tr1::shared_ptr<AbstractNumber>  value,  tr1::shared_ptr<AbstractNumber>  root, char sign)
{
    this->value = value;
    this->root = root;
    this->sign = sign;
    checkValidity(value, root);
}

Radical::~Radical()
{
    //dtor
}

tr1::shared_ptr<AbstractNumber> Radical::add(tr1::shared_ptr<AbstractNumber>number)
{
	if (number->getName() == "Radical" && abs(toDouble() - number->toDouble()) < 0.000001)
		{
			std::vector< tr1::shared_ptr<AbstractNumber> > OutVector;
			tr1::shared_ptr<AbstractNumber> two(new SmartInteger(2));
			tr1::shared_ptr<AbstractNumber> clone(noSign()); // this gets rid of the old sign just in case
			OutVector.push_back(two);
			OutVector.push_back(clone);
			if (number->getSign() == getSign())
			{
				tr1::shared_ptr<AbstractNumber> output(new MultExpression(OutVector, getSign()));
				return output;
			}
			else{
				tr1::shared_ptr<AbstractNumber> output(new SmartInteger(0));
				return output;
			}



		}
		else {
			std::vector< tr1::shared_ptr<AbstractNumber> > OutVector;
			OutVector.push_back(shared_from_this());
			OutVector.push_back(number);
			tr1::shared_ptr<AbstractNumber>output(new SumExpression(OutVector));
			return output;
		}
}

tr1::shared_ptr<AbstractNumber> Radical::multiply(tr1::shared_ptr<AbstractNumber>number)
{
	 char sign;
	 if (getSign() == number->getSign())
	 {
		 sign = '+';
	 }
	 else
	 {
		 sign = '-';
	 }
	 tr1::shared_ptr<AbstractNumber> copy(noSign());
	 //cout << "copy: " << copy->toString()<< endl;
	 tr1::shared_ptr<AbstractNumber> num(number->noSign());

	 //cout << "num: " << num->toString()<< endl;
	 //cout << root->toDouble() << " - " << num->getValue("root")->toDouble() << endl;

	 if (number->getName() == "Radical"){
		 if (  abs(root->toDouble() - num->getValue("root")->toDouble()) < 0.000001)
		 {
			 tr1::shared_ptr<AbstractNumber> output(new Radical(value->multiply(num->getValue("value")), root, sign));
			 return output;
		 }
	 }
	 else if (number->getName() == "Exponent") {
		 if ( abs(number->getValue("base")->toDouble() - toDouble()) < 0.000001 )
		 {
			 std::vector< tr1::shared_ptr<AbstractNumber> > SumVector;
			 tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
			 SumVector.push_back(one);
			 SumVector.push_back(number->getValue("power"));
			 tr1::shared_ptr<AbstractNumber> power(new SumExpression(SumVector));
			 tr1::shared_ptr<AbstractNumber> output(new Exponent(copy, power, sign));
			 return output;
		 }
	 }


	 std::vector< tr1::shared_ptr<AbstractNumber> > MultVector;
	 MultVector.push_back(copy);
	 MultVector.push_back(num);

	 tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector, sign));
	 return r;
}

tr1::shared_ptr<AbstractNumber> Radical::divide(tr1::shared_ptr<AbstractNumber>number)
{
	char sign;
		 if (getSign() == number->getSign())
		 {
			 sign = '+';
		 }
		 else
		 {
			 sign = '-';
		 }
		 tr1::shared_ptr<AbstractNumber> copy(noSign());
		 //cout << "copy: " << copy->toString()<< endl;
		 tr1::shared_ptr<AbstractNumber> num(number->noSign());

		 //cout << "num: " << num->toString()<< endl;
		 //cout << root->toDouble() << " - " << num->getValue("root")->toDouble() << endl;

		 if (number->getName() == "Radical"){
			 if (  abs(root->toDouble() - num->getValue("root")->toDouble()) < 0.000001)
			 {
				 tr1::shared_ptr<AbstractNumber> output(new Radical(value->divide(num->getValue("value")), root, sign));
				 return output;
			 }
		 }
		 else if (number->getName() == "Exponent" && abs(number->getValue("base")->toDouble() - toDouble()) < 0.000001 )
		 	 {
		 		 std::vector< tr1::shared_ptr<AbstractNumber> > SumVector;
		 		 std::vector< tr1::shared_ptr<AbstractNumber> > numer;
		 		 std::vector< tr1::shared_ptr<AbstractNumber> > den;
		 		 tr1::shared_ptr<AbstractNumber> negetive_one(new SmartInteger(1,'-'));
		 		 tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
		 		 SumVector.push_back(number->getValue("power"));
		 		 SumVector.push_back(negetive_one);
		 		 numer.push_back(one);
		 		 tr1::shared_ptr<AbstractNumber> power(new SumExpression(SumVector));
		 		 tr1::shared_ptr<AbstractNumber> exponential(new Exponent(copy, power));
		 		 den.push_back(exponential);
		 		 tr1::shared_ptr<AbstractNumber> output(new MultExpression(numer, den, sign));

		 		 return output;
		 	 }
		 	 std::vector< tr1::shared_ptr<AbstractNumber> > numer;
		 	 std::vector< tr1::shared_ptr<AbstractNumber> > den;
		 	 numer.push_back(copy);
		 	 den.push_back(num);

		 	 tr1::shared_ptr<AbstractNumber> r(new MultExpression(numer, den, sign));
		 	 return r;
}

 tr1::shared_ptr<AbstractNumber>  Radical::simplify()
{
    value = value->simplify();
    root = root->simplify();

    vector< tr1::shared_ptr<AbstractNumber> > SimplifiedTerms;
    int coefficient = 1;
    if (value->getName() == "Integer")
    {
        if (root->getName() == "Integer")
        {
            if (root->toDouble() >= 1)
            {
                int thisValue = abs(value->toDouble());
                for (int i=2; i<=thisValue/2; i++)
                {
                    if (thisValue % (int)round(pow(i, root->toDouble())) == 0)
                    {
                        coefficient*=i;
                        thisValue = thisValue/(int)pow(i, root->toDouble());
                        i = 1;
                    }
                }
                if (coefficient == 1)
                {
                    return shared_from_this();
                }
                if (value->toDouble() < 0)
                    coefficient = coefficient * -1;
                tr1::shared_ptr<AbstractNumber>n1(new SmartInteger(coefficient));
                if (thisValue == 1)
                {
                    return n1;
                }

                else
                {
                    SimplifiedTerms.push_back(n1);
                    tr1::shared_ptr<AbstractNumber>ReducedValue(new SmartInteger(thisValue));
                    tr1::shared_ptr<AbstractNumber>n2(new Radical(ReducedValue, this->root));
                    SimplifiedTerms.push_back(n2);
                }
            }
        }
    }
    else
    {
        return shared_from_this();
    }

    tr1::shared_ptr<AbstractNumber> n (new MultExpression(SimplifiedTerms, '+'));
    if (SimplifiedTerms.size() == 1)
    {
        return n;
    }
    else
    {
        return n->simplify();
    }
}

string Radical::toString()
{
    stringstream ss;
    if (sign == '-')
    {
    	ss << '-';
    }
    if (root->toDouble() == 2)
    {
        ss << "sqrt:";
    }
    else
    {
        ss << root->toString();
        ss << "rt:";
    }
    ss << value->toString();
    return ss.str();
}

double Radical::toDouble()
{
    return pow(value->toDouble(), 1/(root->toDouble()));
}

string Radical::getName()
{
    return "Radical";
}

char Radical::getSign(){
	return sign;
}

tr1::shared_ptr<AbstractNumber> Radical::getValue(string name){
	if (name == "root"){
		return root;
	}
	else if ( name == "value")
	{
		return value;
	}
	else {
		throw "tried to get a " + name + " from a Radical";
	}


}

tr1::shared_ptr<AbstractNumber> Radical::noSign()
{
	tr1::shared_ptr<AbstractNumber> output(new Radical(value, root));
	return output;
}
void Radical::checkValidity(tr1::shared_ptr<AbstractNumber> value, tr1::shared_ptr<AbstractNumber> root)
{
    if (root->toDouble() == 0)
    {
        throw "Roots can't be 0.\nSource: 0rt:";
    }
}
