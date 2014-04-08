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
SumExpression::SumExpression(vector<AbstractNumber*> &nums) {

	this->nums = nums;

}



SumExpression::~SumExpression() {
	// TODO Auto-generated destructor stub
}

AbstractNumber * SumExpression::add(AbstractNumber *number){
    nums.push_back(number);
    return this;
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
        if (nums[i]->getName() != "Integer")
        {
            nums[i] = nums[i]->simplify();
        }
        SimplifiedTerms.push_back(nums[i]);
        cout << SimplifiedTerms[i]->toString() + " ADD TERM" << endl;
    }

    if (SimplifiedTerms.size() == 1)
    {
        return SimplifiedTerms[0]->simplify();
    }
    SumExpression te = SumExpression(SimplifiedTerms);
    cout << te.toString() << endl;
    for (int i=0; (unsigned) i < SimplifiedTerms.size(); i++)
    {
        for (int j=i+1; (unsigned) j < SimplifiedTerms.size(); j++)
        {
            cout <<"ADDING " + SimplifiedTerms[i]->toString() + " " + SimplifiedTerms[j]->toString() << endl;
            tmp = SimplifiedTerms[i]->add(SimplifiedTerms[j]);
            cout <<"ADDING SUCCESS" << endl;
            cout <<tmp->getName()<<endl;
            cout << tmp->toString() << endl;
            //cout << tmp->nums[1]->toString() << endl;
            if (tmp->getName() != "SumExpression")
            {
                SimplifiedTerms[i] = tmp;
                cout <<"ERASING " + SimplifiedTerms[j]->toString()<<endl;
                SimplifiedTerms.erase(SimplifiedTerms.begin() + j);
                j = j - 1;
            }
        }

    }
    cout <<"SUMEXPRESSION CREATED" << endl;
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

vector<AbstractNumber*> SumExpression::getNums()
{
    return nums;
}



