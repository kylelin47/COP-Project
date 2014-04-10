#include <iostream>

using namespace std;

int main() {
    
    /*
    AbstractNumber* num = new SumExpression("e");
    AbstractNumber* nu2 = new SmartInteger("2");
    cout << num->multiply(num2)->toString() << endl;
    
    
    */
    
    
    bool menuLoop = true;
    int input = 0;

    while (menuLoop)
    {
        cout << "1. Compute New Expression" << endl;
        cout << "2. Help" << endl;
        cout << "3. Review Previous Expressions and Answers" << endl;
        cout << "4. Quit" << endl;

        cin>>input;

        if ( !( (1 <= input) && (input <= 4) ) )
        {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Not a valid menu option. Please enter 1, 2, 3, or 4." << endl;
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
                    if (input2.find("back") != string::npos)
                    {
                        keepCompute = false;
                    }
                    else
                    {
                        /*
                        tr1::shared_ptr<AbstractNumber> Int1 (new SmartInteger(25));
                        tr1::shared_ptr<AbstractNumber> Int2 (new SmartInteger(5));

                        vector< tr1::shared_ptr<AbstractNumber> > expression;
                        expression.push_back(Int1);
                        expression.push_back(Int2);

                        SumExpression s = SumExpression(expression);
                        cout << s.toString() << endl;
                        cout << s.simplify()->toString() << endl;
                        s.expression.clear();
                        */
                    }
                }
                break;
            }
            case 2:
                cout << "=====================================================================" << endl;
                cout << "USING THE CALCULATOR" << endl;
                cout << " Use +, -, /, * as their respective operators." << endl;
                cout << " Parentheses and implicit multiplication are supported." << endl;
                cout << " PEMDAS rules will be applied to any expression entered." << endl << endl;
                cout << "SUPPORTED NUMBER TYPES" << endl;
                cout << " \"x to the power of y\" == x^y" << endl;
                cout << " \"the square root of x\" == sqrt:x" << endl;
                cout << " \"the nth root of x\" == nrt:x, where \"n\" is replaced by a number." << endl;
                cout << " \"log base b of x\" == log_b:x" << endl;
                cout << " \"e\" == e" << endl;
                cout << " \"pi\" == pi" << endl;
                cout << "=====================================================================" << endl;
                break;
            case 3:
                break;
            case 4:
                menuLoop = false;
                break;
        }
    }
}
