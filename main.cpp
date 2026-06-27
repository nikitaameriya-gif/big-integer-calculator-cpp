#include "BigInteger.h"

int main() {
    string s1, s2;

    cout << "Enter first big integer: ";
    cin >> s1;

    cout << "Enter second big integer: ";
    cin >> s2;

    BigInteger a(s1);
    BigInteger b(s2);

    cout << "\nA = " << a << endl;
    cout << "B = " << b << endl;

    cout << "\n--- Results ---" << endl;

    cout << "Addition: " << (a + b) << endl;
    cout << "Subtraction (A - B): " << (a - b) << endl;
    cout << "Multiplication: " << (a * b) << endl;

    // Avoid division by zero
    if (!(b == BigInteger("0"))) {
        cout << "Division (A / B): " << (a / b) << endl;
        cout << "Modulus (A % B): " << (a % b) << endl;
    } else {
        cout << "Division and Modulus not possible (division by zero)" << endl;
    }

    cout << "Power (A ^ 2): " << (a ^ 2) << endl;

    return 0;
}
