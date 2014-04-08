#include "Radical.h"

Radical::Radical(AbstractNumber* value, AbstractNumber* root)
{
    this->value = value;
    this->root = root;
}

Radical::~Radical()
{
    //dtor
}

AbstractNumber * Radical::add(AbstractNumber *number)
{
    vector<AbstractNumber*> SumTerms;

    if (number->getName() == "Radical")
    {
        if (number->value == value && number->root == value)
        {
            //do stuff
        }
    }

    else
    {
        static Radical self = Radical(value, root);
        SumTerms.push_back(&self);
        SumTerms.push_back(number);
    }

    static SumExpression s = SumExpression(SumTerms);
    return &s;
}

AbstractNumber * Radical::multiply(AbstractNumber *number)
{
    vector<AbstractNumber*> SimplifiedTerms;
    if (number->getName() == "Radical")
    {
        if (number->root->toDouble() == this->root->toDouble())
        {
            AbstractNumber* newValue = this->value->multiply(number->value);
            static Radical newRad = Radical(newValue->nums[0], this->root);
            newRad = Radical(newValue->nums[0], this->root);
            SimplifiedTerms.push_back(&newRad);

            for (int i=1; (unsigned)i < newValue->nums.size(); i++)
            {
                newRad = Radical(newValue->nums[i], this->root);
                SimplifiedTerms.push_back(&newRad);
            }
        }
    }
    if (number->getName() == "Integer")
    {
        static Radical self = Radical(value, root);

        SimplifiedTerms.push_back(&self);
        SimplifiedTerms.push_back(number);
    }
    static MultExpression m = MultExpression(SimplifiedTerms);

    return &m;
}

AbstractNumber * Radical::divide(AbstractNumber *number)
{

}

AbstractNumber* Radical::simplify()
{
    static Radical newRad = Radical(value, root);
    vector<AbstractNumber*> SimplifiedTerms;
    int coefficient = 1;
    if (value->getName() == "Integer")
    {
        int thisValue = (int)(value->toDouble());
        if (root->getName() == "Integer")
        {
            int rootValue = (int)(root->toDouble());
            if (rootValue >= 1)
            {
                for (int i=2; i<=thisValue/2; i++)
                {
                    if (thisValue % (int)round(pow(i, rootValue)) == 0)
                    {
                        coefficient*=i;
                        thisValue = thisValue/(int)pow(i, rootValue);
                        i = 1;
                    }
                }

                static SmartInteger newValueInt = SmartInteger(coefficient);
                newValueInt = SmartInteger(coefficient);

                if (thisValue == 1)
                {
                    return &newValueInt;
                }

                else
                {
                    SimplifiedTerms.push_back(&newValueInt);
                    newValueInt = SmartInteger(thisValue);
                    newRad = Radical(&newValueInt, this->root);
                    SimplifiedTerms.push_back(&newRad);
                }
            }
        }
    }

    static MultExpression MultTerms = MultExpression(SimplifiedTerms);
    MultTerms = MultExpression(SimplifiedTerms);

    if (SimplifiedTerms.size() == 1)
    {
        return &MultTerms;
    }
    else
    {
        return MultTerms.simplify();
    }
}

string Radical::toString()
{
    stringstream ss;
    if (root->toDouble() == 2)
    {
        ss << "sqrt:";
    }
    else
    {
        ss << root->toString();
        ss << "rt:";
    }
    ss << value->toString();
    return ss.str();
}

double Radical::toDouble()
{
    return pow(value->toDouble(), 1/(root->toDouble()));
}

string Radical::getName()
{
    return "Radical";
}
