#ifndef EXPONENT_H
#define EXPONENT_H
#include "SumExpression.h"
#include "Radical.h"
#include "Log.h"

class Exponent: public AbstractNumber
{
    public:
        Exponent(tr1::shared_ptr<AbstractNumber>, tr1::shared_ptr<AbstractNumber>);
        Exponent(tr1::shared_ptr<AbstractNumber>, tr1::shared_ptr<AbstractNumber>, char sign);
        tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>);
        tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>);
        tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>);
        tr1::shared_ptr<AbstractNumber> simplify();
        string getName();
        string toString();
        double toDouble();
    	char getSign();
    	char calcSign(tr1::shared_ptr<AbstractNumber>);
    	char sign;
    	tr1::shared_ptr<AbstractNumber> getValue(string name);
    	tr1::shared_ptr<AbstractNumber> noSign();

        tr1::shared_ptr<AbstractNumber>base, power;

};

#endif // EXPONENT_H
