#include "Log.h"
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
}

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
}

// Adds number to this and returns the sum
//
// Parameters:
// shared_ptr<AbstractNumber> number	number being added
//
// Returns:
// shared_ptr<AbstractNumber> 			resulting sum of addition
 tr1::shared_ptr<AbstractNumber> Log::add(tr1::shared_ptr<AbstractNumber> number){
	// Base/power identical, return as MultExpression (2*number)
	if(number->getName() == "Exponent"){
		if(number->base == this-> base &&
		   number->power == this->power){
		    vector< tr1::shared_ptr<AbstractNumber> > MultVector;
		    MultVector.push_back(2);
		    MultVector.push_back(number);
		    tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector));
		}
	}

	// Base/power different, return as SumExpression (this + number)
	else{
	    vector< tr1::shared_ptr<AbstractNumber> > SumVector;
	    SumVector.push_back(shared_from_this());
	    SumVector.push_back(number);
	    tr1::shared_ptr<AbstractNumber> r(new SumExpression(SumVector));
	}

    return r;
}

 // Multiplies number by this and returns the product
 //
 // Parameters:
 // shared_ptr<AbstractNumber> number	number being multiplied
 //
 // Returns:
 // shared_ptr<AbstractNumber> 			resulting product of multiplication
 tr1::shared_ptr<AbstractNumber>  Log::multiply(tr1::shared_ptr<AbstractNumber> number){
	 // Base are identical, return as Exponent (b^(p1+p2))
	 if(number->getName() == "Exponent")
		 if(number->base == this->base){
			 vector< tr1::shared_ptr<AbstractNumber> > SumVector;
			 SumVector.push_back(this->power);
			 SumVector.push_back(number->power);
			 tr1::shared_ptr<AbstractNumber> s(new SumExpression(SumVector));
			 tr1::shared_ptr<AbstractNumber> r(new Exponent(this->base,s));
		 }
 	 }

	 // Base are different, return as MultExpression (b1^p*b2^p2)
	 else{
	    vector< tr1::shared_ptr<AbstractNumber> > MultVector;
	    MultVector.push_back(shared_from_this());
	    MultVector.push_back(number);
	    tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector));
	 }

	 return r;
}

// Divides this by number and returns the product
//
// Parameters:
// shared_ptr<AbstractNumber> number	divisor
//
// Returns:
// shared_ptr<AbstractNumber> 			resulting quotient of division
 tr1::shared_ptr<AbstractNumber>  Log::divide(tr1::shared_ptr<AbstractNumber>number){
	 // If Exponent, reverses power by multiplying by -1 if already exponent
	 // Redundant, should still work with below statement
	 /*if(number->getName()=="Exponent"){
		 vector< tr1::shared_ptr<AbstractNumber> > MultVector;
		 MultVector.push_back(SmartInteger(-1));
		 MultVector.push_back(number);
		 tr1::shared_ptr<AbstractNumber> r(new MultExpression(MultVector));
	 }*/

	// Changes number to exponent with power of -1 then multiplies inverted number
	tr1::shared_ptr<AbstractNumber> r(new Exponent(number, new SmartInteger(-1)));
	return multiply(r);
}

// Returns this formatted as a string in the format:
// base^power (e.g. 2^3)
//
// Returns:
// string 			formatted string
string Log::toString(){
	std::stringstream ss;

	ss << base->toString();
	ss << "^";
	ss << power->toString();
	return ss.str();
}


// Returns this as a double
//
// Returns:
// double 			this in double form
double Log::toDouble()
{
	return pow(base->toDouble(), power->toDouble());
}

// Reduces this to simplest form
//
// Returns:
// shared_ptr<AbstractNumber>		number in simplest form
 tr1::shared_ptr<AbstractNumber>  Log::simplify()
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
		 tr1::shared_ptr<AbstractNumber> r new SmartInteger(1);
		 return r;
	 }
	 // if power and base have finite values(i.e. are integers), return integer
	 else if(base->getName() == "Integer" &&
			  power->getName() == "Integer"){
		 tr1::shared_ptr<AbstractNumber> r new SmartInteger((int)toDouble()); // call toDouble and cast as integer
	 }
	 // no simplification possible, return as is
	 else{
		 return this;
	 }
}

// Returns string identifying number type
//
// Returns:
// string 			"Exponent"
string Log::getName()
{
	return "Exponent";
}

// Returns char identifying sign
//
// Returns:
// char 			'+'
char Log::getSign(){
	return '+';
}

