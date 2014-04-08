/*
 * SumExpression.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */

//gsdfagsdagsdagdsgsdagsadgsdag

#include "SumExpression.h"

using namespace std;

/*
void SumExpression::split(vector<MultExpression> &tokens, const string &text, char sep1, char sep2) {
  size_t pos = 0;
  string s = text;
  string sign = "";
  s += '+';
  while ((pos = s.find(sep1)) != string::npos || (pos = s.find(sep2)) != string::npos) {
	  if (s.find(sep1) < s.find(sep2))
	  {
		  pos = s.find(sep1);
	  }
	  else {
		  pos = s.find(sep2);
	  }

	  cout << "Substring:" << s.substr(0 , pos) << endl;
	  tokens.push_back(MultExpression(sign + s.substr(0 , pos)));

	  sign = s[pos];
	  s.erase(0, pos+ 1);
	}



 /*	stringstream ss(text);
	string item;
	while (getline(ss, item, sep1)){

		cout << item << "\n\n";
		tokens.push_back(MultExpression("+" + item));

	}

}
*/
SumExpression::SumExpression(vector<AbstractNumber*> nums) {

	this->nums = nums;

}



SumExpression::~SumExpression() {
	// TODO Auto-generated destructor stub
}

AbstractNumber * SumExpression::add(AbstractNumber *number){
    vector<AbstractNumber*> SumTerms;
    for(int i=0; (unsigned)i < nums.size(); i++)
    {

    }
}
AbstractNumber * SumExpression::multiply(AbstractNumber *number){

}
AbstractNumber * SumExpression::divide(AbstractNumber *number){

}
string SumExpression::toString(){
	string output ="";
	for (int i =0; (unsigned)i < nums.size(); i++){
		output += nums[i]->toString();
		if ((unsigned)i != nums.size() - 1)
        {
            output += " + ";
        }
	}
	return output;
}

double SumExpression::toDouble()
{
    double x = 0;
    for (int i=0; (unsigned)i < nums.size(); i++)
    {
        x = x + nums[i]->toDouble();
    }
	return x;
}

AbstractNumber * SumExpression::simplify()
{
    vector<AbstractNumber*> SimplifiedTerms;

    AbstractNumber *tmp;

    for (int i=0; (unsigned)i < nums.size(); i++)
    {
        SimplifiedTerms.push_back(nums[i]->simplify());
    }
    for (int i=0; (unsigned) i < SimplifiedTerms.size(); i++)
    {
        for (int j=i+1; (unsigned) j < SimplifiedTerms.size(); j++)
        {

            tmp = SimplifiedTerms[i]->add(SimplifiedTerms[j]);

            if (tmp->nums.size() < 2)
            {
                if (tmp->getName() != "SumExpression")
                {
                    SimplifiedTerms[i] = tmp;
                }
                else
                {
                    SimplifiedTerms[i] = tmp->nums[0];
                }

                SimplifiedTerms.erase(SimplifiedTerms.begin() + j);
            }
        }
    }
    static SumExpression simpleSum = SumExpression(SimplifiedTerms);
    simpleSum = SumExpression(SimplifiedTerms);

    if (SimplifiedTerms.size() == this->nums.size())
    {
        return &simpleSum;
    }
    else
    {
        return simpleSum.simplify();
    }
}
string SumExpression::getName()
{
	return "SumExpression";
}




