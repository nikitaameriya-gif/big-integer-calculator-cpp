#include "BigInteger.h"

int main() {
    string num1, num2;
    char op;

    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter operator (+, -, *, /, %, ^): ";
    cin >> op;

    BigInteger a(num1);

    if (op == '^') {
        int power;
        cout << "Enter power: ";
        cin >> power;

        cout << "Result: ";
        (a ^ power).display();
    }
    else {
        cout << "Enter second number: ";
        cin >> num2;

        BigInteger b(num2);

        cout << "Result: ";

        switch (op) {
            case '+':
                (a + b).display();
                break;

            case '-':
                (a - b).display();
                break;

            case '*':
                (a * b).display();
                break;

            case '/':
                (a / b).display();
                break;

            case '%':
                (a % b).display();
                break;

            default:
                cout << "Invalid operator!" << endl;
        }
    }

    return 0;
}
