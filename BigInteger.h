#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BigInteger {
private:
    vector<int> digits;
    bool negative;

public:
    BigInteger();
    BigInteger(string num);

    BigInteger operator+(const BigInteger& other);
    BigInteger operator-(const BigInteger& other);
    BigInteger operator*(const BigInteger& other);
    BigInteger operator/(const BigInteger& other);
    BigInteger operator%(const BigInteger& other);
    BigInteger operator^(int power);

    void display() const;
};

#endif
