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
BigInteger::BigInteger() : m_digits{ 1 }, m_sign{ true } {
    m_digits[0] = 0; 
}

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
}

// literal operator ("raw" version)
BigInteger operator"" _big(const char* literal)
{
    std::string raw{ literal };

    // remove ticks, which can be used for better readability
    std::string::iterator it = std::remove(raw.begin(), raw.end(), '\'');
    raw.erase(it, raw.end());

    // std::string is implicitly converted from std::string to std::string_view
    return BigInteger { raw };
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

size_t BigInteger::size() const { return m_digits.size(); }

bool BigInteger::zero() const { return m_digits.size() == 1 and m_digits[0] == 0; }

// unary arithmetic operators
BigInteger operator+ (const BigInteger& a)
{
    return { a };
}

BigInteger operator- (const BigInteger& a)
{
    BigInteger tmp{ a };

    if (! a.zero()) {
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
    size_t size{ (a.size() >= b.size()) ?
        a.size() + 1 :
        b.size() + 1 };

    std::vector<digit_t> digits(size);

    // add numbers digit per digit
    int carry {};
    for (size_t i{}; i != size; i++)
    {
        if (i < a.size())
            carry += a[i];
        if (i < b.size())
            carry += b[i];

        digits[i] = carry % 10;
        carry /= 10;
    }

    // move result vector into a BigInteger object
    BigInteger tmp{};
    tmp.m_digits = std::move(digits);
    tmp.m_sign = a.sign();
    tmp.removeLeadingZeros();
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
    for (size_t i {}; i != b.size(); ++i)
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
                size_t pos{ i + 1 };
                while (tmp[pos] == 0)
                    pos++;

                // borrow indirectly
                for (size_t k{ pos }; k >= i + 1; --k)
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
    return tmp;
}

BigInteger operator* (const BigInteger& a, const BigInteger& b)
{
    size_t size{ a.size() + b.size() };
    std::vector<digit_t> digits(size);

    digit_t carry {};
    for (size_t i{}; i != size; ++i) {
        digits[i] = carry;
        for (size_t j {}; j != b.size(); ++j) {
            if (i >= j && i - j < a.size()) {
                digits[i] += a[i - j] * b[j];
            }
        }
        carry = digits[i] / 10;
        digits[i] %= 10;
    }

    // move result vector into a BigInteger object
    BigInteger tmp{};
    tmp.m_digits = std::move(digits);
    tmp.m_sign = (a.sign() == b.sign()) ? true : false;
    tmp.removeLeadingZeros();
    return tmp;
}

BigInteger operator/ (const BigInteger& a, const BigInteger& b) 
{
    BigInteger remainder{};
    std::vector<digit_t> result;

    // need positive divisor
    BigInteger bAbs{ b.abs() };

    size_t pos{ a.size() - 1 };

    while (pos != (size_t)-1) {
        // append next digit from dividend to temporary divisor
        size_t len{ (remainder.zero()) ? 1 : remainder.size() + 1 };
        std::vector<digit_t> digits;

        // copy old digits
        for (int k {}; k != len - 1; ++k) {
            digits.push_back(remainder[k]);
        }

        // fetch digit from dividend
        digits.insert(std::begin(digits), a[pos]);

        // move result vector into remainder object
        remainder.m_digits = std::move(digits);
        remainder.m_sign = true;

        // divide current dividend with divisor
        digit_t n {};
        while (bAbs <= remainder) {
            n++;
            remainder -= bAbs;
        }

        result.insert(std::begin(result), n);

        pos--; // fetch next digit from divisor
    }

    // move result vector into a BigInteger object
    BigInteger tmp{};
    tmp.m_digits = std::move(result);
    tmp.m_sign = (a.sign() == b.sign()) ? true : false;
    tmp.removeLeadingZeros();
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

// increment operator: prefix version
BigInteger& operator++ (BigInteger& a)
{
    a += BigInteger{ 1 };
    return a;
}

// decrement operator: prefix version
BigInteger& operator-- (BigInteger& a)
{
    a -= BigInteger{ 1 };
    return a;
}

// increment operator: postfix version
BigInteger operator++ (BigInteger& a, int)
{
    BigInteger tmp{ a };  // construct a copy
    ++a;                  // increment number
    return tmp;           // return the copy
}

// decrement operator: postfix version
BigInteger operator-- (BigInteger& a, int)
{
    BigInteger tmp(a); // construct a copy
    --a;               // decrement number
    return tmp;        // return the copy
}

// type conversion operators
BigInteger::operator int() const
{
    return static_cast<int> (toLongLong());
}

BigInteger::operator long() const
{
    return static_cast<long> (toLongLong());
}

BigInteger::operator long long() const
{
    return static_cast<long long> (toLongLong());
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

BigInteger BigInteger::pow(int exponent)
{
    if (exponent == 0)
        return BigInteger{ 1 };

    BigInteger result { *this };
    if (exponent == 1)
        return result;

    for (int i = 1; i < exponent; i++)
        result = result * *this;

    if (!m_sign && exponent % 2 == 1) {
        result.m_sign = m_sign;
    }

    return result;
}

// private helper operators
digit_t& BigInteger::operator[] (size_t n)
{
    if (n >= m_digits.size()) {
        throw std::invalid_argument("illegal index");
    }

    return m_digits[n];
}

const digit_t& BigInteger::operator[] (size_t n) const
{
    if (n >= m_digits.size()) {
        throw std::invalid_argument("illegal index");
    }

    return m_digits[n];
};

// private helper methods
int BigInteger::compareTo(const BigInteger& a) const 
{
    if (m_sign && !a.m_sign)
        return 1;
    if (!m_sign && a.m_sign)
        return -1;

    int order = 0;
    if (size() < a.size())
    {
        order = -1;
    }
    else if (size() > a.size())
    {
        order = 1;
    }
    else
    {
        for (size_t i = size() - 1; i != (size_t)-1; --i)
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
}

long long BigInteger::toLongLong() const
{
    long long n = 0;
    std::for_each(std::rbegin(m_digits), std::rend(m_digits), [&](digit_t digit) {
        n = 10ll * n + (long long) digit;
     });
    return (m_sign) ? n : -n;
}

void BigInteger::removeLeadingZeros()
{
    // remove trailing zeros, if any ... using STL algorithms
    std::reverse_iterator<std::vector<digit_t>::iterator> r_it{ std::find_if(
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
        [&, i = n.m_digits.size() - 1] (int digit) mutable {
            os << (char)(digit + '0');
            if (i > 0 && i % 3 == 0)
                os << '.';
            --i;
        });

    return os;
}

// functor (supporting formatted output)
std::string BigInteger::operator()(int n)
{
    std::string firstSuffix{};
    std::string subsequentSuffix{ std::string {" "} };

    std::string result{};
    int skippedDigits{};

    if (! m_sign) {
        firstSuffix = std::string{ "-" };
        subsequentSuffix = std::string{ "  " };
    }

    std::reverse_iterator<std::vector<digit_t>::iterator> rev_it = std::rbegin(m_digits);

    // calculate suffix of output
    if (size() % 3 == 1) {
        char digit1 = m_digits.rbegin()[0] + '0'; // ultimate element

        firstSuffix.push_back(digit1);

        subsequentSuffix.append(" ");
        rev_it += 1;
        skippedDigits = 1;
    }
    else if (size() % 3 == 2) {
        char digit1 = m_digits.rbegin()[0] + '0'; // ultimate element
        char digit2 = m_digits.rbegin()[1] + '0'; // penultimate element

        firstSuffix.push_back(digit1);
        firstSuffix.push_back(digit2);

        subsequentSuffix.append("  ");
        rev_it += 2;
        skippedDigits = 2;
    }
    else if (size() % 3 == 0) {
        char digit1 = m_digits.rbegin()[0] + '0'; // ultimate element
        char digit2 = m_digits.rbegin()[1] + '0'; // penultimate element
        char digit3 = m_digits.rbegin()[2] + '0'; // pen-penultimate element
        firstSuffix.push_back(digit1);
        firstSuffix.push_back(digit2);
        firstSuffix.push_back(digit3);
        subsequentSuffix.append("   ");
        rev_it += 3;
        skippedDigits = 3;
    }

    result = firstSuffix;
    result.push_back('.');

    int blocks{ 0 };

    std::for_each(
        rev_it,
        std::rend(m_digits),
        [&, i = m_digits.size() - skippedDigits - 1](int digit) mutable {
        result.push_back ((char)(digit + '0'));
        if (i > 0 && i % 3 == 0) {
            result.push_back('.');
            ++blocks;
        }
        --i;

        if (blocks == n) {
            result.push_back('\n');
            blocks = 0;
            result.append(subsequentSuffix);
        }
    });

    return result;
}

// =====================================================================================
// End-of-File
// =====================================================================================
