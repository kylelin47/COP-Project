#ifndef PI_H
#define PI_H
#include "AbstractNumber.h"

class Pi: public AbstractNumber {
public:
	Pi();
	virtual ~Pi();
	AbstractNumber * add(AbstractNumber *number);
	AbstractNumber * multiply(AbstractNumber *number);
	AbstractNumber * divide(AbstractNumber *number);
	string toString();
	double toDouble();
	AbstractNumber * simplify();
	string getName();
	string getSign();

private:
	double value;
};

#endif // PI_H
