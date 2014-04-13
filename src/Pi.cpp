#include "Pi.h"
#include <cmath>
#include "MultExpression.h"
#include "Exponent.h"

Pi::Pi()
{
    this->sign = '+';
	value = atan(1.0)*4;
}

Pi::Pi(char sign)
{
	value = atan(1.0)*4;
	this->sign = sign;
}

Pi::~Pi()
{
    //dtor
}

tr1::shared_ptr<AbstractNumber> Pi::add(tr1::shared_ptr<AbstractNumber>number){

	//if the thing you're adding is pi; only situation that can add
	//if pi, return multexpression,
	//if it doesn't add, then return sumexpression with number and this

	if (number -> getName() == "Pi")
	{
		if (number -> getSign() == '+' && getSign() == '+')
		{
			vector<tr1::shared_ptr<AbstractNumber> > M;
			tr1::shared_ptr<AbstractNumber> two(new SmartInteger(2));
			M.push_back(two);
			tr1::shared_ptr<AbstractNumber> me(new Pi(sign));
			M.push_back(me);
			tr1::shared_ptr<AbstractNumber> output(new MultExpression(M, '+'));
			return output;
		}

		else if (number -> getSign() == '-' && getSign() == '-')
		{
			vector<tr1::shared_ptr<AbstractNumber> > N;
			tr1::shared_ptr<AbstractNumber> twoN(new SmartInteger(-2));
			N.push_back(twoN);
			tr1::shared_ptr<AbstractNumber> me(new Pi(sign));
			N.push_back(me);
			tr1::shared_ptr<AbstractNumber> output1(new MultExpression(N, '-'));
			return output1;

		}

		else
		{
			vector<tr1::shared_ptr<AbstractNumber> > N;
			tr1::shared_ptr<AbstractNumber> zero(new SmartInteger(0));
			N.push_back(zero);
			tr1::shared_ptr<AbstractNumber> output1(new MultExpression(N, '+'));
			return output1;


		}

	}

	else
	{
		vector<tr1::shared_ptr<AbstractNumber> > N;
		N.push_back(number);
        tr1::shared_ptr<AbstractNumber> me(new Pi(sign));
		N.push_back(me);
		tr1::shared_ptr<AbstractNumber> output1(new SumExpression(N));
		return output1;

	}
}


tr1::shared_ptr<AbstractNumber> Pi::multiply(tr1::shared_ptr<AbstractNumber>number){
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
		 cout << "copy: " << copy->toString()<< endl;
		 tr1::shared_ptr<AbstractNumber> num(number->noSign());

		 cout << "num: " << num->toString()<< endl;
		 cout << toDouble() << " - " << num->toDouble() << endl;

		 if (number->getName() == "Pi")
		 {
			 tr1::shared_ptr<AbstractNumber> two(new SmartInteger(2));
			 tr1::shared_ptr<AbstractNumber> output(new Exponent(copy, two, sign));
			 return output;
		 }
		 else if (number->getName() == "Exponent") {
			 if (abs(number->getValue("base")->toDouble() - toDouble()) < 0.000001 )
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

tr1::shared_ptr<AbstractNumber> Pi::divide(tr1::shared_ptr<AbstractNumber>number){

		if (number -> getName() == "Pi")
		{

			if ((number -> getSign() == '+' && getSign() == '+' ) || (number -> getSign() == '-' && getSign() == '-'))
			{
				tr1::shared_ptr<AbstractNumber> output(new SmartInteger(1));
				return output;
			}

			else
			{
				tr1::shared_ptr<AbstractNumber> output(new SmartInteger(-1));
				return output;
			}

		}

		else if (number -> getName() == "Exponent")
		{
			if (number -> getValue("base") -> getName() == "Pi")
			{
				char newSign;

				if ((number -> getSign() == '+' && getSign() == '+' ) || (number -> getSign() == '-' && getSign() == '-'))
				{
					newSign = '+';
				}

				else
				{
					newSign = '-';
				}

				tr1::shared_ptr<AbstractNumber> num(new SmartInteger(1));
				tr1::shared_ptr<AbstractNumber> exp = number->getValue("power");
				tr1::shared_ptr<AbstractNumber> exp2(new SmartInteger(-1));
                tr1::shared_ptr<AbstractNumber> me(new Pi(sign));
				tr1::shared_ptr<AbstractNumber> ans2(new Exponent(me, exp -> add(exp2)));
				tr1::shared_ptr<AbstractNumber> output2(new MultExpression(num, ans2, newSign));
				return output2;
			}
		}


		else
		{
			char newSign;

			if ((number -> getSign() == '+' && getSign() == '+' ) || (number -> getSign() == '-' && getSign() == '-'))
			{
				newSign = '+';
			}

			else
			{
				newSign = '-';
			}
            tr1::shared_ptr<AbstractNumber> me(new Pi(sign));
			tr1::shared_ptr<AbstractNumber> output2(new MultExpression(me, number, newSign));
			return output2;

		}
		//either return 1 or this

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
	return value;
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
