#ifndef PI_H
#define PI_H
#include "E.h"

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
	char getSign();

private:
	double value;
};

#endif // PI_H
