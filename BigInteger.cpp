#include "BigInteger.h"
#include <algorithm>

BigInteger::BigInteger() {
    number = "0";
}

BigInteger::BigInteger(string num) {
    number = num;
}

bool BigInteger::operator<(const BigInteger& other) {
    if (number.length() != other.number.length())
        return number.length() < other.number.length();

    return number < other.number;
}

BigInteger BigInteger::operator+(const BigInteger& other) {
    string a = number;
    string b = other.number;

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    string result = "";
    int carry = 0;

    int n = max(a.length(), b.length());

    for (int i = 0; i < n; i++) {
        int d1 = (i < a.length()) ? a[i] - '0' : 0;
        int d2 = (i < b.length()) ? b[i] - '0' : 0;

        int sum = d1 + d2 + carry;
        result += (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry)
        result += carry + '0';

    reverse(result.begin(), result.end());

    return BigInteger(result);
}

BigInteger BigInteger::operator-(const BigInteger& other) {
    string a = number;
    string b = other.number;

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    string result = "";
    int borrow = 0;

    for (int i = 0; i < a.length(); i++) {
        int d1 = a[i] - '0' - borrow;
        int d2 = (i < b.length()) ? b[i] - '0' : 0;

        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result += (d1 - d2) + '0';
    }

    while (result.length() > 1 && result.back() == '0')
        result.pop_back();

    reverse(result.begin(), result.end());

    return BigInteger(result);
}

BigInteger BigInteger::operator*(const BigInteger& other) {
    int n = number.size();
    int m = other.number.size();

    vector<int> result(n + m, 0);

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = (number[i] - '0') * (other.number[j] - '0');

            int sum = mul + result[i + j + 1];

            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    string ans = "";

    for (int digit : result) {
        if (!(ans.empty() && digit == 0))
            ans += digit + '0';
    }

    if (ans.empty())
        ans = "0";

    return BigInteger(ans);
}

BigInteger BigInteger::operator/(const BigInteger& other) {
    long long a = stoll(number);
    long long b = stoll(other.number);

    return BigInteger(to_string(a / b));
}

BigInteger BigInteger::operator%(const BigInteger& other) {
    long long a = stoll(number);
    long long b = stoll(other.number);

    return BigInteger(to_string(a % b));
}

BigInteger BigInteger::operator^(int power) {
    BigInteger result("1");

    for (int i = 0; i < power; i++) {
        result = result * (*this);
    }

    return result;
}

void BigInteger::display() const {
    cout << number << endl;
}
