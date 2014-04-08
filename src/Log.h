#ifndef LOG_H
#define LOG_H
#include "SumExpression.h"

class Log: public AbstractNumber
{
    public:
        Log(AbstractNumber *base, AbstractNumber *value);
        AbstractNumber * add(AbstractNumber *number);
        AbstractNumber * multiply(AbstractNumber *number);
        AbstractNumber * divide(AbstractNumber *number);
        string toString();
        double toDouble();
        AbstractNumber* simplify();
        string getName();
        vector<int> primeFactors(int num);

        AbstractNumber *base, *value;
    protected:
    private:
};

#endif // LOG_H
