/*
 * SumExpression.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Alex
 */
#include "SumExpression.h"

using namespace std;

void SumExpression::split(vector<MultExpression> &tokens, const string &text, char sep1, char sep2) {
  size_t pos = 0;
  size_t skipUntil = 0;
  string s = text;
  string sign = "";
  s += '+';
  while ((s.find(sep1, skipUntil)) != string::npos || (s.find(sep2, skipUntil)) != string::npos) {
	  if (s.find(sep1, skipUntil) < s.find(sep2, skipUntil))
	  {
		  pos = s.find(sep1, skipUntil);
	  }
	  else {
		  pos = s.find(sep2, skipUntil);
	  }

	  cout << "Working Substring: " << s.substr(0,pos) << endl;

	  if (count(s.substr(0 , pos), 0, pos, '(') > count(s.substr(0 , pos), 0, pos, ')'))
	  {
		  skipUntil = pos + 1;
		  cout << "Skipping until " << skipUntil << endl;
	  }
	  else
	  {
		  cout << "Substring:" << s.substr(0 , pos) << endl;
		  tokens.push_back(MultExpression(sign + s.substr(0 , pos)));

		  sign = s[pos];
		  s.erase(0, pos+ 1);
		  skipUntil = 0;
	  }
	}

}

SumExpression::SumExpression(const string &input) {

	split(expression, makeStringUsable(input), '+' , '-');
}


SumExpression::SumExpression(vector<AbstractNumber*> &nums) {
    this->nums = nums;
}
int SumExpression::count(string input, int begin, int end, char symbol)
{
	int count = 0;
	for (int i = begin; i <= end; i++)
	{
		if (input[i] == symbol)
		{
			count++;
		}
	}
	return count;
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

string SumExpression::makeStringUsable(string input)
{
	cout << "Starting Make String Usable" << endl;
	string output = input;
	size_t end = input.size();

	//make sure the parenthesis are in check
	while (count(output, 0, output.size(), '(') != count(output, 0, output.size(), ')'))
	{
		cout << output << endl;
		if (count(output, 0, end, '(') > count(output, 0, end, ')'))
		{
			output.insert(end,")");
		}
		else
		{
			output.insert(0,"(");
		}
	}
	end = output.size();
	for (size_t i = 1; i < end; i++) //luckly none the places we want to split at share any charactors
	{
		if ((	output[i] == '(' || //break at (
				output[i] == 'l' || //l for log
				output[i] == 'p' || //p for pi
				output[i] == 'e' || //e is e
				output[i] == 'a' ) //a for ans
				&& output[i-1] != '*' && output[i-1] != '/' && output[i-1] != '+' && output[i-1] != '-' && output[i-1] != '(') //make sure the split point is not already signed
		{
			output.insert(i,"*");
			i++;
			end++;
		}



	}
	cout << "Usable string: "<< output << endl << endl;
	return output;
}
