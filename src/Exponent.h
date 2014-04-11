#ifndef EXPONENT_H
#define EXPONENT_H
#include "SumExpression.h"

class Exponent: public AbstractNumber
{
    public:
        Exponent(tr1::shared_ptr<AbstractNumber>base, tr1::shared_ptr<AbstractNumber>power);
        Exponent(tr1::shared_ptr<AbstractNumber>base, tr1::shared_ptr<AbstractNumber>power, char sign);
        tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>number);
        tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>number);
        tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>number);
        tr1::shared_ptr<AbstractNumber> simplify();
        string getName();
        string toString();
        double toDouble();
    	char getSign();
    	char calcSign(tr1::shared_ptr<AbstractNumber>number);
    	char sign;
    	tr1::shared_ptr<AbstractNumber> getValue(string name);

        tr1::shared_ptr<AbstractNumber>base, power;

};

#endif // EXPONENT_H
