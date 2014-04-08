#ifndef PI_H
#define PI_H
#include "AbstractNumber.h"

class Pi: public AbstractNumber {
public:
	Pi(const string &input);
	virtual ~Pi();
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

#endif // PI_H
