/*
tr1::shared_ptr<AbstractNumber> plus( new Pi());
	tr1::shared_ptr<AbstractNumber> two( new SmartInteger(2));
	tr1::shared_ptr<AbstractNumber> three( new SmartInteger(3));
	tr1::shared_ptr<AbstractNumber> num1( new Radical(plus,two));
	tr1::shared_ptr<AbstractNumber> num4( new Radical(plus,three));
	tr1::shared_ptr<AbstractNumber> num3( new Exponent(plus,two));
	tr1::shared_ptr<AbstractNumber> num2( new Pi('-'));
	cout << num1->toString() << " * " << plus->toString() << " = " << num4->multiply(plus)->toString() << endl;

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



