#ifndef EXPONENT_H
#define EXPONENT_H
#include "SumExpression.h"

class Exponent: public AbstractNumber
{
    public:
        Exponent(tr1::shared_ptr<AbstractNumber>, tr1::shared_ptr<AbstractNumber>);
        tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>);
        tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>);
        tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>);
        tr1::shared_ptr<AbstractNumber> simplify();
        string getName();
        string toString();
        double toDouble();
    	char getSign();

        tr1::shared_ptr<AbstractNumber>base, value;

};

#endif // EXPONENT_H
