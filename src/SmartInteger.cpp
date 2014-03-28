/*
 * SmartInteger.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

#include "SmartInteger.h"

using namespace std;

SmartInteger::SmartInteger(const string &input) {

	stringstream ss(input);

	ss >> value;

}



SmartInteger::~SmartInteger() {
	// TODO Auto-generated destructor stub
}

vector<AbstractNumber*> SmartInteger::add(AbstractNumber *number){

}
vector<AbstractNumber*> SmartInteger::multiply(AbstractNumber *number){

}
vector<AbstractNumber*> SmartInteger::divide(AbstractNumber *number){

}
string SmartInteger::toString(){
	stringstream ss;

	ss << value;
	return ss.str();
}

double SmartInteger::toDouble()
{
	return 0;
}

bool SmartInteger::simplify()
{
	return false;
}
string SmartInteger::getName()
{
	return "SmartInteger";
}



