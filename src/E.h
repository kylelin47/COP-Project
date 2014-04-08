#ifndef E_H
#define E_H
#include "AbstractNumber.h"

class E: public AbstractNumber {
public:
	E(const string &input);
	virtual ~E();
	AbstractNumber * add(AbstractNumber *number);
	AbstractNumber * multiply(AbstractNumber *number);
	AbstractNumber * divide(AbstractNumber *number);
	string toString();
	double toDouble();
	AbstractNumber * simplify();
	string getName();

private:
	double value;
};

#endif // E_H
