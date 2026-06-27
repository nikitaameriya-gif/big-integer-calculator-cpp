#include "BigInteger.h"

int main() {
    BigInteger a("123456789123456789");
    BigInteger b("987654321987654321");

    cout << "A = " << a << endl;
    cout << "B = " << b << endl;

    cout << "\nAddition: " << (a + b) << endl;
    cout << "Subtraction: " << (b - a) << endl;
    cout << "Multiplication: " << (a * b) << endl;
    cout << "Division: " << (b / a) << endl;
    cout << "Modulus: " << (b % a) << endl;
    cout << "Power: " << (BigInteger("12") ^ 5) << endl;

    return 0;
}
