#ifndef E_H
#define E_H
#include "Log.h"

class E: public AbstractNumber {
public:
	E();
	virtual ~E();
	tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>number);
	tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>number);
	string toString();
	double toDouble();
	tr1::shared_ptr<AbstractNumber> simplify();
	string getName();
	char getSign();

private:
	double value;
};

#endif // E_H
