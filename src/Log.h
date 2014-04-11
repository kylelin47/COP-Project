#ifndef LOG_H
#define LOG_H
#include "SumExpression.h"

class Log: public AbstractNumber
{
    public:
        Log(tr1::shared_ptr<AbstractNumber>base, tr1::shared_ptr<AbstractNumber>value);
        Log(tr1::shared_ptr<AbstractNumber>base, tr1::shared_ptr<AbstractNumber>value, char sign);
        tr1::shared_ptr<AbstractNumber> add(tr1::shared_ptr<AbstractNumber>number);
        tr1::shared_ptr<AbstractNumber> multiply(tr1::shared_ptr<AbstractNumber>number);
        tr1::shared_ptr<AbstractNumber> divide(tr1::shared_ptr<AbstractNumber>number);
        string toString();
        double toDouble();
         tr1::shared_ptr<AbstractNumber>  simplify();
        string getName();
        vector<int> primeFactors(int num);
    	char getSign();

        tr1::shared_ptr<AbstractNumber>base, value;
    protected:
    private:
        char sign;
};

#endif // LOG_H
