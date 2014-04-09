#ifndef Radical_H
#define Radical_H
#include "SumExpression.h"
#include "math.h"
class Radical: public AbstractNumber
{
    public:
        Radical(AbstractNumber* value, AbstractNumber* root);
        ~Radical();
        AbstractNumber* root;
        AbstractNumber* value;
        AbstractNumber * add(AbstractNumber *number);
        AbstractNumber * multiply(AbstractNumber *number);
        AbstractNumber * divide(AbstractNumber *number);
        string toString();
        double toDouble();
        AbstractNumber * simplify();
        string getName();
        char getSign();

    protected:
    private:
};

#endif // Radical_H
