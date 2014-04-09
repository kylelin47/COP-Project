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
        cout <<"ADDING INTEGER" << endl;
        SumTerms.push_back(this);
        SumTerms.push_back(number);
    }

    AbstractNumber *s = new SumExpression(SumTerms);
    return s;
}

AbstractNumber * Radical::multiply(AbstractNumber *number)
{
    vector<AbstractNumber*> SimplifiedTerms;
    if (number->getName() == "Radical")
    {
        if (number->root->toDouble() == this->root->toDouble())
        {
            AbstractNumber* newValue = this->value->multiply(number->value);
            AbstractNumber* n = new Radical(newValue->nums[0], this->root);
            SimplifiedTerms.push_back(n);

            for (int i=1; (unsigned)i < newValue->nums.size(); i++)
            {
                n = new Radical(newValue->nums[i], this->root);
                SimplifiedTerms.push_back(n);
            }
        }
    }
    if (number->getName() == "Integer")
    {

        SimplifiedTerms.push_back(this);
        SimplifiedTerms.push_back(number);
    }
    AbstractNumber *m = new MultExpression(SimplifiedTerms);
    SimplifiedTerms.clear();
    return m;
}

AbstractNumber * Radical::divide(AbstractNumber *number)
{

}

AbstractNumber* Radical::simplify()
{
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
                AbstractNumber *n1 = new SmartInteger(coefficient);
                if (coefficient == 1)
                {
                    return this;
                }

                if (thisValue == 1)
                {
                    return n1;
                }

                else
                {
                    SimplifiedTerms.push_back(n1);
                    AbstractNumber *n2 = new Radical(n1, this->root);
                    SimplifiedTerms.push_back(n2);
                }
            }
        }
    }
    else
    {
        return this;
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

char Radical::getSign(){
	return '+';
}
