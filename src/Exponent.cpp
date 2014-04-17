#include "Exponent.h"
#include <cmath>

using namespace std;

// Constructor for Exponent
// Represents an exponent where "b" is base and "p" is power:
// b^p (b to the power p)
//
// Parameters:
// shared_ptr<AbstractNumber> base		number being raised to a given exponent
// shared_ptr<AbstractNumber> power		power the number a given number is being raised to
Exponent::Exponent(tr1::shared_ptr<AbstractNumber> base,
				   tr1::shared_ptr<AbstractNumber> power)
{
	// No invalid bases or powers
    this->base = base;
    this->power = power;
    this->sign = '+';
}

// Alternate constructor for Exponent
// Represents an exponent where "b" is base and "p" is power:
// +/-b^p (b to the power p)
//
// Parameters:
// shared_ptr<AbstractNumber> base		number being raised to a given exponent
// shared_ptr<AbstractNumber> power		power the number a given number is being raised to
// char sign							'+'/'-' representation of positive/negative
Exponent::Exponent(tr1::shared_ptr<AbstractNumber> base,
				   tr1::shared_ptr<AbstractNumber> power,
				   char sign)
{
	// No invalid bases or powers
    this->base = base;
    this->power = power;
    this->sign = sign;
}

// Adds number to this and returns the sum
//
// Parameters:
// shared_ptr<AbstractNumber> number	number being added
//
// Returns:
// shared_ptr<AbstractNumber> 			resulting sum of addition
 tr1::shared_ptr<AbstractNumber> Exponent::add(tr1::shared_ptr<AbstractNumber> number){
 	// Checks for cancellation
 	number = number->simplify();
 	if(abs(toDouble() - number->toDouble()) < 0.000001 &&
 	   this->getSign() != number->getSign()){
 		tr1::shared_ptr<AbstractNumber> r(new SmartInteger(0));

 	    return r;
 	}
 	// Checks for duplication/simplification
 	else if(abs(toDouble() - number->toDouble()) < 0.000001 &&
 			this->getSign() == number->getSign()){
 		vector< tr1::shared_ptr<AbstractNumber> > MultVector;
		tr1::shared_ptr<AbstractNumber> i(new SmartInteger(2));
		MultVector.push_back(i);
		tr1::shared_ptr<AbstractNumber> me(new Exponent(base, power, sign));
		MultVector.push_back(me);
		tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector, '+'));

	    return r;
  	}

    //Can't tell if they add or not
 	else if(number->getName() == "SumExpression" ||
            number->getName() == "MultExpression"){
 	    return number->add(shared_from_this());
 	}
    // Duplication necessary for simplification
 	// Assuming number is in simplest form

 	// No simplification possible
	else{
		vector< tr1::shared_ptr<AbstractNumber> > SumVector;
		tr1::shared_ptr<AbstractNumber> me(new Exponent(base, power, sign));
		SumVector.push_back(me);
		SumVector.push_back(number);
		tr1::shared_ptr<AbstractNumber> r(new SumExpression(SumVector));

	    return r;
	}

}

 // Multiplies number by this and returns the product
 //
 // Parameters:
 // shared_ptr<AbstractNumber> number	number being multiplied
 //
 // Returns:
 // shared_ptr<AbstractNumber> 			resulting product of multiplication
tr1::shared_ptr<AbstractNumber>  Exponent::multiply(tr1::shared_ptr<AbstractNumber> number){
	// Checks for simplification if both exponents
	number = number->simplify();

	if(number->getName() == "Exponent"){
        tr1::shared_ptr<Exponent> givenNumber = tr1::static_pointer_cast<Exponent>(number);
		if(abs(givenNumber->getValue("base")->toDouble() - base->toDouble()) < 0.000001){
			tr1::shared_ptr<AbstractNumber> r(new Exponent(base, power->add(givenNumber->getValue("power")), this->calcSign(number)));
		    return r;
		}
	else if (number->getName() == "Radical") {
		 if (abs(number->getValue("value")->toDouble() - base->toDouble()) < 0.000001 )
		 {
			 std::vector< tr1::shared_ptr<AbstractNumber> > SumVector;
			 tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
			 tr1::shared_ptr<AbstractNumber> invertedRoot(new MultExpression(one, number->getValue("root")->noSign(), number->getValue("root")->getSign()));
			 SumVector.push_back(power);
			 SumVector.push_back(invertedRoot);
			 tr1::shared_ptr<AbstractNumber> power(new SumExpression(SumVector));
			 tr1::shared_ptr<AbstractNumber> output(new Exponent(number->getValue("value")->noSign(), power, sign));
			 return output;
		 }
	}
        else{
            tr1::shared_ptr<AbstractNumber> me(new Exponent(base, power, sign));
            tr1::shared_ptr<AbstractNumber> r(new MultExpression(me, number, this->calcSign(number)));
            return r;
        }
	}

	// Checks for simplification if number = base
	// Adds 1 to exponent
	else if(abs(number->toDouble() - base->toDouble()) < 0.000001 ){
		tr1::shared_ptr<AbstractNumber> c(new SmartInteger(1));
		tr1::shared_ptr<AbstractNumber> r(new Exponent(base, power->add(c), this->calcSign(number)));
	    return r;
	}
	else if(number->getName() == "SumExpression" || number->getName() == "MultExpression")
    {
        return number->multiply(shared_from_this());
    }

    vector< tr1::shared_ptr<AbstractNumber> > MultVector;
    tr1::shared_ptr<AbstractNumber> me(new Exponent(base, power, sign));
    MultVector.push_back(me);
    MultVector.push_back(number);
    tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector, '+'));

    return r;
}

// Divides this by number and returns the product
//
// Parameters:
// shared_ptr<AbstractNumber> number	divisor
//
// Returns:
// shared_ptr<AbstractNumber> 			resulting quotient of division
tr1::shared_ptr<AbstractNumber>  Exponent::divide(tr1::shared_ptr<AbstractNumber>number){
	// Reverses sign if exponent and multiplies
	if(number->getName()=="Exponent"){
        tr1::shared_ptr<Exponent> givenNumber = tr1::static_pointer_cast<Exponent>(number);
		if(givenNumber->getSign()=='-'){
			tr1::shared_ptr<AbstractNumber> r(new Exponent(givenNumber->getValue("base"), givenNumber->getValue("power")));
			return multiply(r);
		}
		else{
            tr1::shared_ptr<AbstractNumber> nOne(new SmartInteger(-1));
            tr1::shared_ptr<AbstractNumber> newPower = givenNumber->getValue("power")->multiply(nOne);
			tr1::shared_ptr<AbstractNumber> r(new Exponent(givenNumber->getValue("base"), newPower, givenNumber->getSign()));
			return multiply(r);
		}
	}

	// Subtracts 1 from power if base = number
	else if(number->toDouble() == base->toDouble()){
		tr1::shared_ptr<AbstractNumber> c(new SmartInteger(-1));
		tr1::shared_ptr<AbstractNumber> r(new Exponent(base, power->add(c), this->calcSign(number)));
		return r;
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
        tr1::shared_ptr<AbstractNumber> reversedMultE(new MultExpression(MultEDem, MultENum, '+'));
        return reversedMultE->multiply(shared_from_this());
    }

    vector< tr1::shared_ptr<AbstractNumber> > NumVector;
    tr1::shared_ptr<AbstractNumber> me(new Exponent(base, power, sign));
    NumVector.push_back(me);
    vector< tr1::shared_ptr<AbstractNumber> > DenVector;
    DenVector.push_back(number);
    tr1::shared_ptr<AbstractNumber> r(new MultExpression(NumVector, DenVector, this->calcSign(number)));
    return r;
}

// Returns this formatted as a string in the format:
// base^power (e.g. 2^3)
//
// Returns:
// string 			formatted string
string Exponent::toString(){
	std::stringstream ss;
	if (sign == '-')
	{
		ss << '-';
	}
	if (power->toDouble() == 1)
	{
		return base->toString();
	}
	if (base->getName() == "Log" || base->getName() == "Radical" || base->getName() == "MultExpression")
	{
		ss << "(";
	}
	ss << base->toString();
	if (base->getName() == "Log" || base->getName() == "Radical" || base->getName() == "MultExpression")
	{
		ss << ")";
	}
	ss << "^";
	ss << power->toString();
	return ss.str();
}


// Returns this as a double
//
// Returns:
// double 			this in double form
double Exponent::toDouble()
{
	if (sign == '-')
	{
		return -1*pow(base->toDouble(), power->toDouble());
	}
	return pow(base->toDouble(), power->toDouble());
}

// Reduces this to simplest form
//
// Returns:
// shared_ptr<AbstractNumber>		number in simplest form
 tr1::shared_ptr<AbstractNumber>  Exponent::simplify()
{
    base = base->simplify();
    power = power->simplify();
	// simplifies exponents with logarithmic power
	 if(power->getName() == "Log"){
        tr1::shared_ptr<Log> numLog = tr1::static_pointer_cast<Log>(power);
		 if(numLog->getValue("base")->toDouble() == base->toDouble()){
			 return numLog->getValue("value");
		 }
	 }
	 // if base = 0, returns integer 0
	 if(base->toDouble() == 0){
		 tr1::shared_ptr<AbstractNumber> r(new SmartInteger(0));
		 return r;
	 }
	 // if base = 1, returns integer 1
	 else if(base->toDouble() == 1){
		 tr1::shared_ptr<AbstractNumber> r(new SmartInteger(1));
		 return r;
	 }
	 // if power = 0, returns 1
	 else if(power->toDouble() == 0){
		 tr1::shared_ptr<AbstractNumber> r(new SmartInteger(1));
		 return r;
	 }
	 //if power = 1, return base
	 else if (power->toDouble() == 1){
	     return base;
	 }
	 // if power and base have finite values(i.e. are integers), return integer
	 else if(base->getName() == "Integer" &&
			  power->getName() == "Integer" &&
              power->toDouble() > 0){
		 tr1::shared_ptr<AbstractNumber> r(new SmartInteger((int)round(toDouble()))); // call toDouble and cast as integer
	 	 return r;
	 }
	 // simplifies radicals
	 else if(base->getName() == "Radical"){
	     tr1::shared_ptr<Radical> baseRad = tr1::static_pointer_cast<Radical>(base);
		 if(fmod(power->toDouble(),baseRad->getValue("root")->toDouble()) == 0){
			 tr1::shared_ptr<AbstractNumber> r(new Exponent(baseRad->getValue("value"), power->divide(baseRad->getValue("root")), sign));
			 return r;
		 }
	 }
	 // simplifies exponents of exponents
	 else if(base->getName() == "Exponent"){
	     tr1::shared_ptr<Exponent> baseExp = tr1::static_pointer_cast<Exponent>(base);
		 tr1::shared_ptr<AbstractNumber> r(new Exponent(baseExp->getValue("base"), power->multiply(baseExp->getValue("power")), sign));
		 return r;
	 }
	 else if (abs(1/toDouble() - round(1/toDouble())) < 0.00001)
    {
        tr1::shared_ptr<AbstractNumber>n(new SmartInteger(1));
        tr1::shared_ptr<AbstractNumber>n2(new SmartInteger((int)round(1/toDouble())));
        tr1::shared_ptr<AbstractNumber>nF(new MultExpression(n, n2, '+'));
        return nF;
    }
	 // no simplification possible, return as is
	return shared_from_this();

}

// Returns string identifying number type
//
// Returns:
// string 			"Exponent"
string Exponent::getName()
{
	return "Exponent";
}

// Returns char identifying sign
//
// Returns:
// char 			'+' or '-'
char Exponent::getSign(){
	return sign;
}

// Returns char identifying sign resulting from multiplication or division of two numbers
//
// Returns:
// char 			'+' or '-'
char Exponent::calcSign(tr1::shared_ptr<AbstractNumber> number){
	if(sign == number->getSign()){
		return '+';
	}
	else{
		return '-';
	}
}

// Takes in a string representing a variable name and returns the given variable
//
// Parameters
// string name					name of the variable to be returned
//
// Returns:
// shared_ptr<AbstractNumber>	value of variable
tr1::shared_ptr<AbstractNumber> Exponent::getValue(string name){
	if (name == "base") {
		return base;
	}
	else if (name == "power")
	{
		return power;
	}
	else
	{
		const char* msg = ("tried to get" + name + "from an exponent").c_str();
		throw NumException(msg);
	}
}

tr1::shared_ptr<AbstractNumber> Exponent::noSign()
{
	tr1::shared_ptr<AbstractNumber> output(new Exponent(base, power));
	return output;
}
