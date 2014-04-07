#include "Radical.h"

Radical::Radical(AbstractNumber* value, AbstractNumber* root, int coefficient)
{
    this->value = value;
    this->root = root;
    this->coefficient = coefficient;
}

Radical::~Radical()
{
    //dtor
}

vector<AbstractNumber*> Radical::add(AbstractNumber *number)
{

}

vector<AbstractNumber*> Radical::multiply(AbstractNumber *number)
{
    vector<AbstractNumber*> Mult;
    if (number->getName() == "Radical")
    {
        if (number->root->toDouble() == this->root->toDouble())
        {
            int newCoefficient = this->coefficient * number->coefficient;
            vector<AbstractNumber*> newValue = this->value->multiply(number->value);
            Radical newRad = Radical(newValue[0], this->root, newCoefficient);
            AbstractNumber *num = &newRad;
            Mult.push_back(num);
            for (int i=1; (unsigned)i < newValue.size(); i++)
            {
                newRad = Radical(newValue[i], this->root, newCoefficient);
                num = &newRad;
                Mult.push_back(num);
            }
        }
    }
    if (number->getName() == "Integer")
    {

    }

    return Mult;
}

vector<AbstractNumber*> Radical::divide(AbstractNumber *number)
{

}

bool Radical::simplify()
{
    bool simplified = false;
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
                    if (thisValue % (int)pow(i, rootValue) == 0)
                    {
                        coefficient*=i;
                        thisValue = thisValue/(int)pow(i, rootValue);
                        i = 1;
                        simplified = true;
                    }
                }
            }
        }
    }
    return simplified;
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
    return coefficient*pow(value->toDouble(), 1/(root->toDouble()));
}

string Radical::getName()
{
    return "Radical";
}
