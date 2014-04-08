#include <iostream>
#include "SmartInteger.h"
#include "Radical.h"
#include "Log.h"

using namespace std;

int main() {

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
                        SmartInteger Int1 = SmartInteger(25);
                        SmartInteger Int2 = SmartInteger(2);
                        Radical Rad1 = Radical(&Int1, &Int2);
                        Log Log1 = Log(&Int2, &Int1);
                        AbstractNumber *n1 = Int1.add(&Int2);
                        AbstractNumber *n2 = n1->add(&Rad1);
                        cout << "" << endl;
                        //AbstractNumber *n3 = n1->add(n2);
                        //cout << n3->toString() << endl;
                        AbstractNumber *n4 = n2->simplify();
                        cout << n2->toString() << endl;
                        cout << n4->toString() << endl;
                        cout << Log1.simplify()->toString() << endl;
                    }
                }
                break;
            }
            case 2:
                cout << "USING THE CALCULATOR" << endl;
                cout << " \"x to the power of y\" == x^y" << endl;
                cout << " \"the square root of x\" == sqrt:x" << endl;
                cout << " \"the nth root of x\" == nrt:x, where \"n\" is replaced by a number." << endl;
                cout << " \"log base b of x\" == log_b:x" << endl;
                break;
            case 3:
                break;
            case 4:
                menuLoop = false;
                break;
        }
    }
}
