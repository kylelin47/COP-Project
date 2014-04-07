#include "Radical.h"

Radical::Radical(AbstractNumber* value, AbstractNumber* root)
{
    this->value = value;
    this->root = root;
    this->coefficient = 1;
}

Radical::~Radical()
{
    //dtor
}

vector<AbstractNumber*> Radical::add(AbstractNumber *number)
{

}

vector<AbstractNumber*> Radical::multiply(AbstractNumber *number);
{

}

vector<AbstractNumber*> Radical::divide(AbstractNumber *number);
{

}

bool Radical::simplify()
{
    bool simplified = false;
    if value.getName() == "Integer"
    {
        int thisValue = value.value;
        if (root.getName() == "Integer")
        {
            int rootValue = root.value;
            if (rootValue >= 1)
            {
                for (i=2; i<=thisValue/2; i++)
                {
                    if (thisValue % (int)pow(i, rootValue) == 0)
                    {
                        coefficient*=i;
                        thisValue = thisValue/pow;
                        i = 1;
                        simplified = true;
                    }
                }
            }
        }
    }
    return simplified;
}
