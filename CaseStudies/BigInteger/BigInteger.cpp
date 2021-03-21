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
BigInteger::BigInteger() : m_digits{ 1 }, m_length{ 1 }, m_sign{ true } {}

BigInteger::BigInteger(std::string_view sv) : m_length{0}, m_sign{ true }
{
    std::reverse_iterator<std::string_view::iterator> r = sv.rbegin();

    std::for_each(std::rbegin(sv), std::prev(std::rend(sv)), [this](char ch) {
        std::cout << '#' << ch << '#'  << std::endl;

        if (! std::isdigit(ch)) {
            throw std::invalid_argument("illegal digit in big number");
        }
        m_digits.push_back(ch - '0');
        m_length++;
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
        m_length++;
    }

    std::cout << '!' << ch << '!' << std::endl;
}

// output
std::ostream& operator<< (std::ostream& os, const BigInteger& n)
{
    if (!n.m_sign)
        os << '-';

    // TODO:Da muss was anderes her
    for (int i = n.m_length - 1; i >= 0; i--)
    {
        os << n.m_digits[i];
        if (i > 0 && i % 3 == 0)
            os << '.';
    }

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
