#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BigInteger {
private:
    vector<int> digits;   // stores digits in reverse order
    bool negative;

    void trim();
    static int compareAbs(const BigInteger &a, const BigInteger &b);
    static BigInteger addAbs(const BigInteger &a, const BigInteger &b);
    static BigInteger subAbs(const BigInteger &a, const BigInteger &b);

public:
    // Constructors
    BigInteger();
    BigInteger(string num);
    BigInteger(long long num);

    // Utility
    string toString() const;

    // Operators
    BigInteger operator+(const BigInteger &other) const;
    BigInteger operator-(const BigInteger &other) const;
    BigInteger operator*(const BigInteger &other) const;
    BigInteger operator/(const BigInteger &other) const;
    BigInteger operator%(const BigInteger &other) const;
    BigInteger operator^(long long power) const;

    // Comparison
    bool operator<(const BigInteger &other) const;
    bool operator==(const BigInteger &other) const;

    friend ostream& operator<<(ostream &out, const BigInteger &num);
};

#endif
