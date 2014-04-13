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
			M.push_back(shared_from_this());
			tr1::shared_ptr<AbstractNumber> output(new MultExpression(M, '+'));
			return output;
		}

		else if (number -> getSign() == '-' && getSign() == '-')
		{
			vector<tr1::shared_ptr<AbstractNumber> > N;
			tr1::shared_ptr<AbstractNumber> twoN(new SmartInteger(-2));
			N.push_back(twoN);
			N.push_back(shared_from_this());
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
		N.push_back(shared_from_this());
		tr1::shared_ptr<AbstractNumber> output1(new SumExpression(N));
		return output1;

	}
}


tr1::shared_ptr<AbstractNumber> Pi::multiply(tr1::shared_ptr<AbstractNumber>number){

	//if pi, return exponent with pi and 2
	//otherwise, return multexpression of number and pi
	//create multexpression with shared_from_this() and number
	//if it's an exponent, check to see if base is pi, return exponent with base pi, and power the number's(given) power plus 1

	if(number -> getName() == "Pi")
	{
//		vector<tr1::shared_ptr<AbstractNumber> > A;
		tr1::shared_ptr<AbstractNumber> exp(new SmartInteger(2));
//		A.push_back(exp);
		tr1::shared_ptr<AbstractNumber> ans(new Exponent(shared_from_this(), exp));
		return ans;


//		tr1::shared_ptr<AbstractNumber> ans(new Exponent(shared_from_this(), 2));
//		return ans;

	}

	else if (number -> getName() == "Exponent")
	{
		if (number -> getValue("base") -> getName() == "Pi")
		{
			tr1::shared_ptr<AbstractNumber> exp = number->getValue("power");
			tr1::shared_ptr<AbstractNumber> exp2(new SmartInteger(1));

			tr1::shared_ptr<AbstractNumber> ans2(new Exponent(shared_from_this(), exp -> add(exp2)));
			return ans2;
		}
	}


	else if (number -> getName() == "SumExpression" || number -> getName() == "MultExpression")
	{
        return number->multiply(shared_from_this());
	}
	else
    {
        vector<tr1::shared_ptr<AbstractNumber> > M;
	    M.push_back(number);
	    M.push_back(shared_from_this());
		tr1::shared_ptr<AbstractNumber> ans3(new MultExpression(M, '+'));
		return ans3;
    }

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
				tr1::shared_ptr<AbstractNumber> ans2(new Exponent(shared_from_this(), exp -> add(exp2)));
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

			tr1::shared_ptr<AbstractNumber> output2(new MultExpression(shared_from_this(), number, newSign));
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
