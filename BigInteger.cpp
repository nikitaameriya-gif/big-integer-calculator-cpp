#include "BigInteger.h"

// ---------------- Constructors ----------------
BigInteger::BigInteger() {
    negative = false;
    digits.push_back(0);
}

BigInteger::BigInteger(string num) {
    negative = false;
    if (num[0] == '-') {
        negative = true;
        num = num.substr(1);
    }

    for (int i = num.size() - 1; i >= 0; i--)
        digits.push_back(num[i] - '0');

    trim();
}

BigInteger::BigInteger(long long num) {
    if (num < 0) {
        negative = true;
        num = -num;
    } else negative = false;

    if (num == 0) digits.push_back(0);

    while (num) {
        digits.push_back(num % 10);
        num /= 10;
    }
}

// ---------------- Utility ----------------
void BigInteger::trim() {
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();

    if (digits.size() == 1 && digits[0] == 0)
        negative = false;
}

string BigInteger::toString() const {
    string s = negative ? "-" : "";
    for (int i = digits.size() - 1; i >= 0; i--)
        s += (digits[i] + '0');
    return s;
}

ostream& operator<<(ostream &out, const BigInteger &num) {
    out << num.toString();
    return out;
}

// ---------------- Comparison ----------------
int BigInteger::compareAbs(const BigInteger &a, const BigInteger &b) {
    if (a.digits.size() != b.digits.size())
        return a.digits.size() < b.digits.size() ? -1 : 1;

    for (int i = a.digits.size() - 1; i >= 0; i--) {
        if (a.digits[i] != b.digits[i])
            return a.digits[i] < b.digits[i] ? -1 : 1;
    }
    return 0;
}

bool BigInteger::operator<(const BigInteger &other) const {
    if (negative != other.negative)
        return negative;

    int cmp = compareAbs(*this, other);
    if (negative)
        return cmp > 0;
    return cmp < 0;
}

bool BigInteger::operator==(const BigInteger &other) const {
    return negative == other.negative && digits == other.digits;
}

// ---------------- Absolute operations ----------------
BigInteger BigInteger::addAbs(const BigInteger &a, const BigInteger &b) {
    BigInteger res;
    res.digits.clear();

    int carry = 0;
    int n = max(a.digits.size(), b.digits.size());

    for (int i = 0; i < n || carry; i++) {
        int sum = carry;
        if (i < a.digits.size()) sum += a.digits[i];
        if (i < b.digits.size()) sum += b.digits[i];

        res.digits.push_back(sum % 10);
        carry = sum / 10;
    }

    return res;
}

BigInteger BigInteger::subAbs(const BigInteger &a, const BigInteger &b) {
    BigInteger res;
    res.digits.clear();

    int borrow = 0;

    for (int i = 0; i < a.digits.size(); i++) {
        int diff = a.digits[i] - borrow - (i < b.digits.size() ? b.digits[i] : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else borrow = 0;

        res.digits.push_back(diff);
    }

    res.trim();
    return res;
}

// ---------------- + operator ----------------
BigInteger BigInteger::operator+(const BigInteger &other) const {
    if (negative == other.negative) {
        BigInteger res = addAbs(*this, other);
        res.negative = negative;
        return res;
    }

    if (compareAbs(*this, other) >= 0) {
        BigInteger res = subAbs(*this, other);
        res.negative = negative;
        return res;
    } else {
        BigInteger res = subAbs(other, *this);
        res.negative = other.negative;
        return res;
    }
}

// ---------------- - operator ----------------
BigInteger BigInteger::operator-(const BigInteger &other) const {
    BigInteger temp = other;
    temp.negative = !temp.negative;
    return *this + temp;
}

// ---------------- * operator ----------------
BigInteger BigInteger::operator*(const BigInteger &other) const {
    BigInteger res;
    res.digits.assign(digits.size() + other.digits.size(), 0);

    for (int i = 0; i < digits.size(); i++) {
        for (int j = 0; j < other.digits.size(); j++) {
            res.digits[i + j] += digits[i] * other.digits[j];
            res.digits[i + j + 1] += res.digits[i + j] / 10;
            res.digits[i + j] %= 10;
        }
    }

    res.negative = negative != other.negative;
    res.trim();
    return res;
}

// ---------------- / operator (simple long division) ----------------
BigInteger BigInteger::operator/(const BigInteger &other) const {
    BigInteger dividend = *this;
    BigInteger divisor = other;

    dividend.negative = divisor.negative = false;

    BigInteger result;
    result.digits.assign(dividend.digits.size(), 0);

    BigInteger current;

    for (int i = dividend.digits.size() - 1; i >= 0; i--) {
        current.digits.insert(current.digits.begin(), dividend.digits[i]);
        current.trim();

        int x = 0;
        while (compareAbs(current, divisor) >= 0) {
            current = subAbs(current, divisor);
            x++;
        }
        result.digits[i] = x;
    }

    result.negative = negative != other.negative;
    result.trim();
    return result;
}

// ---------------- % operator ----------------
BigInteger BigInteger::operator%(const BigInteger &other) const {
    BigInteger div = *this / other;
    return *this - (div * other);
}

// ---------------- ^ power ----------------
BigInteger BigInteger::operator^(long long power) const {
    BigInteger base = *this;
    BigInteger result("1");

    while (power > 0) {
        if (power % 2 == 1)
            result = result * base;

        base = base * base;
        power /= 2;
    }

    return result;
}
