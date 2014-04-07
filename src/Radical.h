#ifndef Radical_H
#define Radical_H
#include "MultExpression.h"
#include "math.h"
class Radical: public AbstractNumber
{
    public:
        Radical(AbstractNumber* value, AbstractNumber* root, int coefficient);
        ~Radical();
        AbstractNumber* root;
        AbstractNumber* value;
        vector<AbstractNumber*> add(AbstractNumber *number);
        vector<AbstractNumber*> multiply(AbstractNumber *number);
        vector<AbstractNumber*> divide(AbstractNumber *number);
        string toString();
        double toDouble();
        bool simplify();
        string getName();
        int coefficient;
    protected:
    private:
};

#endif // Radical_H
