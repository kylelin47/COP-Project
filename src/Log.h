#ifndef LOG_H
#define LOG_H
#include "AbstractNumber.h"

class Log: public AbstractNumber
{
    public:
        Log(AbstractNumber *base, AbstractNumber *value);
        vector<AbstractNumber*> add(AbstractNumber *number);
        vector<AbstractNumber*> multiply(AbstractNumber *number);
        vector<AbstractNumber*> divide(AbstractNumber *number);
        string toString();
        double toDouble();
        bool simplify();
        string getName();
        vector<int> primeFactors(int num);

        AbstractNumber *base, *value;
    protected:
    private:
};

#endif // LOG_H
