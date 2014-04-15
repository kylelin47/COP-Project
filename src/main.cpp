#include <iostream>
#include "SmartInteger.h"
#include "SumExpression.h"
#include "Log.h"
#include "Pi.h"
#include "Exponent.h"
#include "Radical.h"
#include <exception>
#include "History.h"
//#include "AbstractNumber.h"

string history;

tr1::shared_ptr<AbstractNumber> historyAns;


using namespace std;




void printHelp() {

	cout << "=====================================================================" << endl;
	cout << "|                     *USING THE CALCULATOR*                        |" << endl;
	cout << "|===================================================================|" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|     Parentheses and implicit multiplication are supported.        |" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|     PEMDAS rules will be applied to any expression entered.       |" << endl;
	cout << "|     Use +, -, /, * as their respective operators.                 |" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|                  No double operators such as: *-                  |" << endl;
	cout << "|===================================================================|" << endl;
	cout << "|                    SUPPORTED NUMBER TYPES                         |" << endl;
	cout << "|===================================================================|" << endl;
	cout << "|\"x added to y\" == x+y                                              |" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|\"y subtracted from x\" == x-y                                       |" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|\"x multiplied by y\" == x*y                                         |" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|\"x divided by y\" == x/y                                            |" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
    cout << "|\"x to the power of y\" == x^y                                       |" << endl;
    cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|\"the square root of x\" == sqrt:x                                   |" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|\"the nth root of x\" == nrt:x, where \"n\" is replaced by a number    |" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|\"log base b of x\" == log_b:x                                       |" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|\"e\" == e                                                           |" << endl;
	cout << "|-------------------------------------------------------------------|" << endl;
	cout << "|\"pi\" == pi                                                         |" << endl;
	cout << "=====================================================================" << endl;
}
int main() {

  vector< tr1::shared_ptr<AbstractNumber> > ansHistory;
  vector<string>  expHistory;
  bool menuLoop = true;
    int input = 0;
    int setAns;
    cout << "||||   WELCOME   ||||" << endl;
    cout << "||||   TO OUR    ||||" << endl;
    cout << "|||| CALCULATOR  ||||" << endl;
    cout << " _____________________ " << endl;
    cout << "|  _________________  |" << endl;
    cout << "| |               0 | |" << endl;
    cout << "| |_________________| |" << endl;
    cout << "|  ___ ___ ___   ___  |" << endl;
    cout << "| | 7 | 8 | 9 | | + | |" << endl;
    cout << "| |___|___|___| |___| |" << endl;
    cout << "| | 4 | 5 | 6 | | - | |" << endl;
    cout << "| |___|___|___| |___| |" << endl;
    cout << "| | 1 | 2 | 3 | | x | |" << endl;
    cout << "| |___|___|___| |___| |" << endl;
    cout << "|_____________________|" << endl;

    while (menuLoop)
    {
    	cout << "\nPlease enter one of the options below: " << endl;
    	cout << "=================================================" << endl;
        cout << "1. Compute New Expression                       |" << endl;
        cout << "=================================================" << endl;
        cout << "2. Help                                         |" << endl;
        cout << "=================================================" << endl;
        cout << "3. Review Previous Expressions and Answers      |" << endl;
        cout << "=================================================" << endl;
        cout << "4. Quit                                         |" << endl;
        cout << "=================================================\n" << endl;

        cin>>input;

        if ( !( (1 <= input) && (input <= 4) ) )
        {
            cin.clear();
            while (cin.get() != '\n');
            cout << "\nNot a valid menu option. Please enter 1, 2, 3, or 4." << endl;
            continue;
        }

        switch (input)
        {
            case 1:
            {
                cin.ignore();
                bool keepCompute = true;
                while (keepCompute)
                {

                    string input2;
                    cout << "Enter the expression to compute. (Type 'back' to go back to the main menu)" << endl;
                    getline(cin, input2);
                    if(input2 != "")
                    {


                    	if (input2.find("back") != string::npos)
                    	{
                    		keepCompute = false;
                    	}
                    	else
                    	{

                    				try{
                    					if(input2.rfind("ans") != std::string::npos)
                    					{
                        				unsigned found = input2.rfind("ans");
                                        if (history == "")
                                            history = "0";
                    					input2.replace(found, std::string("ans").length(), "(" + history + ")");

                    					tr1::shared_ptr<AbstractNumber> num(new SumExpression(input2,true));
                    					historyAns = num->simplify();
                    					cout << "Result: \n" << historyAns->toString() << endl;
                    					ansHistory.push_back(historyAns);
                    					history = input2;
                    					expHistory.push_back(history);
                    					}
                    					else
                    					{
                    						tr1::shared_ptr<AbstractNumber> num(new SumExpression(input2,true));
                    						historyAns = num->simplify();
                    						cout << "Result: \n" << historyAns->toString() << endl;
                    						ansHistory.push_back(historyAns);
                    						history = input2;
                    						expHistory.push_back(history);
                    					}


                    				}
                    				catch(exception &msg)
                    				{

                    					cout << "***ERROR: "<< msg.what() << "***"  << endl;
                    				}



                    		}
                    	}
                    else
                    {
                    	cout << "Result: Invalid Expression\n" << endl;
                    }
                }


                break;
            }
            case 2:
                printHelp();

                break;
            case 3:
            	if(ansHistory.size() == 0)
            	{
            		cout << "Please enter some expressions before viewing this option." << endl;
            	}
            	else
            	{
            	cout << "The previous answer was: " << historyAns->toString() << endl;
            	cout << "The previous answer as a decimal: " << historyAns->toDouble() << endl;
            	cout << "This answer may be used in further calculations by using the keyword 'ans'" << endl;
            	cout << "\nThe previous expressions and answers calculated are as follows: " << endl;

            	for(int i=0; i<ansHistory.size(); i++)

            	{

            		cout << "(#" << (ansHistory.size()-i) << ")" << "Expression: " << expHistory[i] << endl;
            		cout << "Answer: " << ansHistory[i]->toString() << "\n" << endl;

            	}




            		cout << "To set 'ans' to a previous expressions's answer, please enter the corresponding digit: " << endl;
            		cin>>setAns;

            		if(!( (1 <= setAns) && (setAns <= ansHistory.size()) ))
            		{

            			cin.clear();
            			while (cin.get() != '\n');
            			cout << "\nNot a valid menu option. Please enter 1-10." << endl;
            			continue;
            		}

            			else if(((1 <= setAns) && (setAns <= ansHistory.size()))== 1)
            			{
            			history = ansHistory[ansHistory.size() - setAns]->toString();


            		}
            		else
            		{
            			cout << "\nNot a valid menu option. Please enter 1-10." << endl;
            		}

            	}
                break;
            case 4:
            	cout << "The calculator will now exit. Thank you!" << endl;
                menuLoop = false;
                break;
        }
    }
}

