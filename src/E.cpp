#include "E.h"
#include <cmath>
#include "MultExpression.h"
#include "Exponent.h"

E::E()
{
    this->sign = '+';
	value = exp(1.0);
}

E::E(char sign)
{
	value = exp(1.0);
    this->sign = sign;
}

E::~E()
{
    //dtor
}

tr1::shared_ptr<AbstractNumber> E::getValue(string name){
	const char* msg = ("tried to get" + name + "from an E()").c_str();
	throw NumException(msg);
}

tr1::shared_ptr<AbstractNumber> E::add(tr1::shared_ptr<AbstractNumber>number){

	if (number -> getName() == "E")
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
	else if(number->getName() == "MultExpression" || number->getName() == "SumExpression")
    {
        return number->add(shared_from_this());
    }

    vector<tr1::shared_ptr<AbstractNumber> > N;
    N.push_back(number);
    N.push_back(shared_from_this());
    tr1::shared_ptr<AbstractNumber> output1(new SumExpression(N));
    return output1;

}

tr1::shared_ptr<AbstractNumber> E::multiply(tr1::shared_ptr<AbstractNumber>number){

    if(number -> getName() == "E")
	{

		tr1::shared_ptr<AbstractNumber> exp(new SmartInteger(2));
		tr1::shared_ptr<AbstractNumber> ans(new Exponent(shared_from_this(), exp));
		return ans;
	}

	else if (number -> getName() == "Exponent")
	{
	    tr1::shared_ptr<Exponent> numExp = tr1::static_pointer_cast<Exponent>(number);
		if (numExp -> getValue("base") -> getName() == "E")
		{
			tr1::shared_ptr<AbstractNumber> exp = numExp->getValue("power");
			tr1::shared_ptr<AbstractNumber> exp2(new SmartInteger(1));

			tr1::shared_ptr<AbstractNumber> ans2(new Exponent(shared_from_this(), exp -> add(exp2)));
			return ans2;
		}
	}
	else if (number->getName() == "Radical") {
		 if (abs(number->getValue("value")->toDouble() - toDouble()) < 0.000001 )
		 {
			 std::vector< tr1::shared_ptr<AbstractNumber> > SumVector;
			 tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
			 tr1::shared_ptr<AbstractNumber> invertedRoot(new MultExpression(one, number->getValue("root")->noSign(), number->getValue("root")->getSign()));
			 SumVector.push_back(one);
			 SumVector.push_back(invertedRoot);
			 tr1::shared_ptr<AbstractNumber> power(new SumExpression(SumVector));
			 tr1::shared_ptr<AbstractNumber> output(new Exponent(number->getValue("value")->noSign(), power, sign));
			 return output;
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

    else if(number->getName() == "MultExpression")
    {
        return number->multiply(shared_from_this());
    }
    vector<tr1::shared_ptr<AbstractNumber> > M;
    M.push_back(number);
    M.push_back(shared_from_this());
    tr1::shared_ptr<AbstractNumber> ans3(new MultExpression(M, '+'));
    return ans3;

}

tr1::shared_ptr<AbstractNumber> E::divide(tr1::shared_ptr<AbstractNumber>number){

		if (number -> getName() == "E")
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
		    tr1::shared_ptr<Exponent> numExp = tr1::static_pointer_cast<Exponent>(number);
			if (numExp -> getValue("base") -> getName() == "E")
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
        else if(number->getName() == "MultExpression")
        {
            tr1::shared_ptr<MultExpression> MultE = tr1::static_pointer_cast<MultExpression>(number);
            vector<tr1::shared_ptr<AbstractNumber> > MultENum = MultE->getNumerator();
            vector<tr1::shared_ptr<AbstractNumber> > MultEDem = MultE->getDenominator();
            if (MultEDem.size() == 0)
            {
                tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
                MultEDem.push_back(one);
            }
            tr1::shared_ptr<AbstractNumber> reversedMultE(new MultExpression(MultEDem, MultENum, number->getSign()));
            return reversedMultE->multiply(shared_from_this());
        }
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

string E::toString(){
	if (sign == '-')
	{
		return "-e";
	}
	return "e";
}

double E::toDouble()
{
	return value;
}

tr1::shared_ptr<AbstractNumber> E::simplify()
{
	return shared_from_this();
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
