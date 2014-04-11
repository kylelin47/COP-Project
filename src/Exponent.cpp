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
 	if(this->toDouble() == number->toDouble() &&
 	   this->getSign() != number->getSign()){
 		tr1::shared_ptr<AbstractNumber> r(new SmartInteger(0));

 	    return r;
 	}
 	// Checks for duplication/simplification
 	else if(this->toDouble() == number->toDouble() &&
 			this->getSign() == number->getSign()){
 		vector< tr1::shared_ptr<AbstractNumber> > MultVector;
		tr1::shared_ptr<AbstractNumber> i(new SmartInteger(2));
		MultVector.push_back(i);
		MultVector.push_back(shared_from_this());
		tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector, sign));

	    return r;
  	}
 	// Duplication necessary for simplification
 	// Assuming number is in simplest form
 	
 	// No simplification possible
	else{	
		vector< tr1::shared_ptr<AbstractNumber> > SumVector;
		SumVector.push_back(shared_from_this());
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
	if(number->getName() == "Exponent"){
		if(number->getValue("base") == base){
			tr1::shared_ptr<AbstractNumber> r(new Exponent(base, power->add(number->getValue("power")), this->calcSign(number)));

		    return r;
		}
	}
	
	// Checks for simplification if number = base
	// Adds 1 to exponent
	else if(number->toDouble() == base->toDouble()){
		tr1::shared_ptr<AbstractNumber> c(new SmartInteger(1));
		tr1::shared_ptr<AbstractNumber> r(new Exponent(base, power->add(c), this->calcSign(number)));
	    return r;
	}
	
	else{
		vector< tr1::shared_ptr<AbstractNumber> > MultVector;
		MultVector.push_back(shared_from_this());
		MultVector.push_back(number);
		tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector, '+'));

		return r;
	}
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
		if(number->getSign()=='-'){
			tr1::shared_ptr<AbstractNumber> r(new Exponent(number->getValue("base"), number->getValue("power")));
			return multiply(r);
		}
		else{
			tr1::shared_ptr<AbstractNumber> r(new Exponent(number->getValue("base"), number->getValue("power"),'-'));
			return multiply(r);
		}
	}
	
	// Subtracts 1 from power if base = number
	else if(number->toDouble() == base->toDouble()){
		tr1::shared_ptr<AbstractNumber> c(new SmartInteger(1,'-'));
		tr1::shared_ptr<AbstractNumber> r(new Exponent(base, power->add(c), this->calcSign(number)));
		return r;
	}
	
	else{
	 	tr1::shared_ptr<AbstractNumber> t(this);
		vector< tr1::shared_ptr<AbstractNumber> > NumVector;
		NumVector.push_back(shared_from_this());
		vector< tr1::shared_ptr<AbstractNumber> > DenVector;
		DenVector.push_back(shared_from_this());
		tr1::shared_ptr<AbstractNumber> r(new MultExpression(NumVector, DenVector, this->calcSign(number)));
		return r;
	}
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

	ss << base->toString();
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
	return pow(base->toDouble(), power->toDouble());
}

// Reduces this to simplest form
//
// Returns:
// shared_ptr<AbstractNumber>		number in simplest form
 tr1::shared_ptr<AbstractNumber>  Exponent::simplify()
{
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
	 // if power and base have finite values(i.e. are integers), return integer
	 else if(base->getName() == "Integer" &&
			  power->getName() == "Integer"){
		 tr1::shared_ptr<AbstractNumber> r(new SmartInteger((int)toDouble())); // call toDouble and cast as integer
	 	 return r;
	 }
	 // no simplification possible, return as is
	 else{
	 	 tr1::shared_ptr<AbstractNumber> r(this);
		 return r;
	 }
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
		return sign;
	}
	else{
		return '-';
	}
}

// Takes in a string representing a variable name and returns the given variable
//
// Paramters
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
		cout << "tried to get a " + name + " from an exponent" << endl;
		throw "tried to get a " + name + " from an exponent";
	}
}

tr1::shared_ptr<AbstractNumber> Exponent::noSign()
{
	tr1::shared_ptr<AbstractNumber> output(new Exponent(base, power));
	return output;
}
