#include "Radical.h"

Radical::Radical( tr1::shared_ptr<AbstractNumber>  value,  tr1::shared_ptr<AbstractNumber>  root)
{
    this->value = value;
    this->root = root;
}

Radical::~Radical()
{
    //dtor
}

tr1::shared_ptr<AbstractNumber> Radical::add(tr1::shared_ptr<AbstractNumber>number)
{
    vector< tr1::shared_ptr<AbstractNumber> > SumTerms;

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
        SumTerms.push_back(shared_from_this());
        SumTerms.push_back(number);
    }

    tr1::shared_ptr<AbstractNumber>s(new SumExpression(SumTerms));
    return s;
}

tr1::shared_ptr<AbstractNumber> Radical::multiply(tr1::shared_ptr<AbstractNumber>number)
{
    vector< tr1::shared_ptr<AbstractNumber> > SimplifiedTerms;
    if (number->getName() == "Radical")
    {
        if (number->root->toDouble() == this->root->toDouble())
        {
            tr1::shared_ptr<AbstractNumber> newValue = this->value->multiply(number->value);
            tr1::shared_ptr<AbstractNumber> n(new Radical(newValue->expression[0], this->root));
            SimplifiedTerms.push_back(n);
        }
    }
    if (number->getName() == "Integer")
    {

        SimplifiedTerms.push_back(shared_from_this());
        SimplifiedTerms.push_back(number);
    }
    tr1::shared_ptr<AbstractNumber>m(new MultExpression(SimplifiedTerms));
    SimplifiedTerms.clear();
    return m;
}

tr1::shared_ptr<AbstractNumber> Radical::divide(tr1::shared_ptr<AbstractNumber>number)
{

}

 tr1::shared_ptr<AbstractNumber>  Radical::simplify()
{
    vector< tr1::shared_ptr<AbstractNumber> > SimplifiedTerms;
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
                tr1::shared_ptr<AbstractNumber>n1(new SmartInteger(coefficient));
                if (coefficient == 1)
                {
                    return shared_from_this();
                }

                if (thisValue == 1)
                {
                    return n1;
                }

                else
                {
                    SimplifiedTerms.push_back(n1);
                    tr1::shared_ptr<AbstractNumber>n2(new Radical(n1, this->root));
                    SimplifiedTerms.push_back(n2);
                }
            }
        }
    }
    else
    {
        return shared_from_this();
    }

    tr1::shared_ptr<AbstractNumber> n (new MultExpression(SimplifiedTerms));

    if (SimplifiedTerms.size() == 1)
    {
        return n;
    }
    else
    {
        return n->simplify();
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
