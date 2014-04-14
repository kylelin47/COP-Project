/*
 * History.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: Alex
 */

#include "History.h"
#include "AbstractNumber.h"

using namespace std;

History::History() {


}

History::~History() {
	// TODO Auto-generated destructor stub
}

void History::addHistory(string input) {
	this->history.push_back(input);
	this->historyNum = this->history.size()-1;
}

void History::setHistroy(int num){
	if (num >= 0 && num < history.size())
	{
		historyNum = num;
	}
	else
	{
		throw NumException((const char*)"Value out of range for SetHistory");
	}
}

string History::getHistory()
{
	return history[historyNum];
}



