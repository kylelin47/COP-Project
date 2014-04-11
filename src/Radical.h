#ifndef Radical_H
#define Radical_H
#include "SumExpression.h"
#include "math.h"
class Radical: public AbstractNumber
{
    public:
        Radical( tr1::shared_ptr<AbstractNumber>  value,  tr1::shared_ptr<AbstractNumber>  root);
        Radical( tr1::shared_ptr<AbstractNumber>  value,  tr1::shared_ptr<AbstractNumber>  root, char sign);
        ~Radical();
         tr1::shared_ptr<AbstractNumber>  root;
         tr1::shared_ptr<AbstractNumber>  value;
        tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>number);
        tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>number);
        tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>number);
        string toString();
        double toDouble();
        tr1::shared_ptr<AbstractNumber> simplify();
        string getName();
        char getSign();
        tr1::shared_ptr<AbstractNumber> getValue(string name);
        tr1::shared_ptr<AbstractNumber> noSign();

    protected:
    private:
        char sign;
};

#endif // Radical_H
