// =====================================================================================
// BigInteger.cpp
// =====================================================================================

#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "BigInteger.h"

// c'tors / d'tor
BigInteger::BigInteger() : m_digits{ 1 }, m_length{ 1 }, m_sign{ true } { m_digits[0] = 0; }

BigInteger::BigInteger(std::string_view sv) : m_sign{ true }
{
    std::reverse_iterator<std::string_view::iterator> r = sv.rbegin();

    std::for_each(std::rbegin(sv), std::prev(std::rend(sv)), [this](char ch) {
        if (ch == '.') {
            return;
        }
        else if (! std::isdigit(ch)) {
            throw std::invalid_argument("illegal digit in big number");
        }
        else {
            m_digits.push_back(ch - '0');
        }
    });

    char ch = *std::prev(std::rend(sv));
    if (ch == '+' or ch == '-') {
        m_sign = (ch == '-') ? false : true;
    }
    else {
        if (!std::isdigit(ch)) {
            throw std::invalid_argument("illegal digit in big number");
        }
        m_digits.push_back(ch - '0');
    }

    removeLeadingZeros();

    m_length = m_digits.size();
}

// type conversion c'tors
BigInteger::BigInteger(int n)
{
    toBigInteger(n);
}

BigInteger::BigInteger(long n) 
{
    toBigInteger(n);
}

BigInteger::BigInteger(long long n)
{
    toBigInteger(n);
}

// getter
bool BigInteger::sign() const { return m_sign; }

int BigInteger::cardinality() const { return m_length; }

bool BigInteger::isNull() const { return m_length == 1 and m_digits[0] == 0; }

// unary arithmetic operators
BigInteger operator+ (const BigInteger& a)
{
    return { a };
}

BigInteger operator- (const BigInteger& a)
{
    BigInteger tmp{ a };

    if (!a.isNull()) {
        tmp.m_sign = !tmp.m_sign;
    }

    return tmp;
}

// binary arithmetic operators
BigInteger operator+ (const BigInteger& a, const BigInteger& b)
{
    // handle sign and change operation
    if (a.sign() != b.sign())
        return (a.sign()) ? a - b.abs() : b - a.abs();

    // need vector
    int size{ (a.cardinality() >= b.cardinality()) ?
        a.cardinality() + 1 :
        b.cardinality() + 1 };

    std::vector<int> digits(size);

    // add numbers digit per digit
    size_t carry {};
    for (size_t i{}; i != size; i++)
    {
        if (i < a.cardinality())
            carry += a[i];
        if (i < b.cardinality())
            carry += b[i];

        digits[i] = carry % 10;
        carry /= 10;
    }

    // move result vector into a BigInteger object
    BigInteger tmp{};
    tmp.m_digits = std::move(digits);
    tmp.removeLeadingZeros();
    tmp.m_sign = a.sign();
    tmp.m_length = tmp.m_digits.size();
    return tmp;
}

BigInteger operator- (const BigInteger& a, const BigInteger& b)
{
    // handle sign and change operation
    if (a.sign() != b.sign())
        return (a.sign()) ? a + b.abs() : -(a.abs() + b);

    if (a.abs() < b.abs())
        return (a.sign()) ? -(b - a) : b.abs() - a.abs();

    // create copy of minuend
    BigInteger tmp{ a };

    // traverse digits of subtrahend
    for (int i = 0; i < b.cardinality(); i++)
    {
        if (tmp[i] < b[i])
        {
            if (tmp[i + 1] != 0)
            {
                tmp[i + 1]--;
                tmp[i] += 10;
            }
            else
            {
                // preceding digit is zero, cannot borrow directly
                int pos{ i + 1 };
                while (tmp[pos] == 0)
                    pos++;

                // borrow indirectly
                for (int k{ pos }; k >= i + 1; k--)
                {
                    tmp[k]--;
                    tmp[k - 1] += 10;
                }
            }
        }

        // subtract current subtrahend digit from minuend digit
        tmp[i] -= b[i];
    }

    tmp.removeLeadingZeros();
    tmp.m_length = tmp.m_digits.size();
    return tmp;
}

BigInteger operator* (const BigInteger& a, const BigInteger& b)
{
    int size{ a.cardinality() + b.cardinality() };
    std::vector<int> digits(size);

    int carry {};
    for (int i{}; i < size; i++)
    {
        digits[i] = carry;
        for (int j {}; j < b.cardinality(); j++) {
            if (i - j >= 0 && i - j < a.cardinality()) {
                digits[i] += a[i - j] * b[j];
            }
        }
        carry = digits[i] / 10;
        digits[i] %= 10;
    }

    // move result vector into a BigInteger object
    BigInteger tmp{};
    tmp.m_digits = std::move(digits);
    tmp.removeLeadingZeros();
    tmp.m_sign = (a.sign() == b.sign()) ? true : false;
    tmp.m_length = tmp.m_digits.size();
    return tmp;
}

BigInteger operator/ (const BigInteger& a, const BigInteger& b) 
{
    BigInteger remainder{};
    std::vector<int> result;

    // need positive divisor
    BigInteger bAbs{ b.abs() };

    int pos{ a.cardinality() - 1 };

    while (pos >= 0)
    {
        // append next digit from dividend to temporary divisor
        int len{ (remainder.isNull()) ? 1 : remainder.cardinality() + 1 };
        std::vector<int> digits;

        // copy old digits
        for (int k {}; k < len - 1; k++) {
            digits.push_back(remainder[k]);
        }

        // fetch digit from dividend
        digits.insert(std::begin(digits), a[pos]);

        // move result vector into remainder object
        remainder.m_digits = std::move(digits);
        remainder.m_sign = true;
        remainder.m_length = remainder.m_digits.size();

        // divide current dividend with divisor
        int n {};
        while (bAbs <= remainder)
        {
            n++;
            remainder -= bAbs;
        }

        result.insert(std::begin(result), n);

        // fetch next digit from divisor
        pos--;
    }

    // move result vector into a BigInteger object
    BigInteger tmp{};
    tmp.m_digits = std::move(result);
    tmp.removeLeadingZeros();
    tmp.m_sign = (a.sign() == b.sign()) ? true : false;
    tmp.m_length = tmp.m_digits.size();
    return tmp;
}

BigInteger operator% (const BigInteger& a, const BigInteger& b)
{
    return a - b * (a / b);
}

// arithmetic-assignment operators
BigInteger& operator+= (BigInteger& a, const BigInteger& b)
{
    a = a + b;
    return a;
}

BigInteger& operator-= (BigInteger& a, const BigInteger& b)
{
    a = a - b;
    return a;
}

BigInteger& operator*= (BigInteger& a, const BigInteger& b)
{
    a = a * b;
    return a;
}

BigInteger& operator/= (BigInteger& a, const BigInteger& b)
{
    a = a / b;
    return a;
}

BigInteger& operator%= (BigInteger& a, const BigInteger& b)
{
    a = a % b;
    return a;
}

// comparison operators
bool operator== (const BigInteger& a, const BigInteger& b)
{
    return (a.compareTo(b) == 0) ? true : false;
}

bool operator!= (const BigInteger& a, const BigInteger& b)
{
    return !(a == b);
}

bool operator< (const BigInteger& a, const BigInteger& b)
{
    return (a.compareTo(b) < 0) ? true : false;
}

bool operator<= (const BigInteger& a, const BigInteger& b)
{
    return (a.compareTo(b) <= 0) ? true : false;
}

bool operator> (const BigInteger& a, const BigInteger& b)
{
    return b < a;
}

bool operator>= (const BigInteger& a, const BigInteger& b)
{
    return b <= a;
}

// public helper methods
BigInteger BigInteger::abs() const
{
    BigInteger tmp{ *this };
    tmp.m_sign = true;
    return tmp;
}

// private helper operators
int& BigInteger::operator[] (int n)
{
    if (n < 0 or n >= m_length) {
        throw std::invalid_argument("illegal index");
    }

    return m_digits[n];
}

const int& BigInteger::operator[] (int n) const 
{
    if (n < 0 or n >= m_length) {
        throw std::invalid_argument("illegal index");
    }

    return m_digits[n];
};

// private helper methods
int BigInteger::compareTo(const BigInteger& a) const {
    if (m_sign && !a.m_sign)
        return 1;
    if (!m_sign && a.m_sign)
        return -1;

    int order = 0;
    if (cardinality() < a.cardinality())
    {
        order = -1;
    }
    else if (cardinality() > a.cardinality())
    {
        order = 1;
    }
    else
    {
        for (int i = cardinality() - 1; i >= 0; i--)
        {
            if (m_digits[i] < a.m_digits[i])
            {
                order = -1;
                break;
            }
            else if (m_digits[i] > a.m_digits[i])
            {
                order = 1;
                break;
            }
        }
    }

    return (m_sign) ? order : -order;
}

void BigInteger::toBigInteger(long long n)
{
    // handle sign
    m_sign = true;
    if (n < 0)
    {
        m_sign = false;
        n *= -1;
    }

    // extract digits from number
    while (n != 0)
    {
        m_digits.push_back(n % 10);
        n /= 10;
    }

    removeLeadingZeros();
    m_length = m_digits.size();
}

void BigInteger::removeLeadingZeros()
{
    // remove trailing zeros, if any ... using STL algorithms
    std::reverse_iterator<std::vector<int>::iterator> r_it{ std::find_if(
        std::rbegin(m_digits),
        std::rend(m_digits),
        [](int value) { return value != 0; }
    ) };

    // vector contains only '0's - rescue last '0'
    if (r_it == std::rend(m_digits)) {
        r_it--;
    }

    m_digits.erase(r_it.base(), std::end(m_digits));
}

// output
std::ostream& operator<< (std::ostream& os, const BigInteger& n)
{
    if (!n.m_sign)
        os << '-';

    std::for_each(
        std::rbegin(n.m_digits), 
        std::rend(n.m_digits),
        [&,i = n.m_length - 1] (int digit) mutable {
            os << (char)(digit + '0');
            if (i > 0 && i % 3 == 0)
                os << '.';
            --i;
        });

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
