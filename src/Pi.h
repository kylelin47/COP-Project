#ifndef PI_H
#define PI_H
#include "E.h"

class Pi: public AbstractNumber {
public:
	Pi();
	Pi(char sign);
	virtual ~Pi();
	tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>number);
	string toString();
	double toDouble();
	tr1::shared_ptr<AbstractNumber> simplify();
	string getName();
	char getSign();

private:
	int sign;
	double value;
};

#endif // PI_H
