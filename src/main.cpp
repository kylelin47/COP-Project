#include <iostream>
#include "SumExpression.h"

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
                break;
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
