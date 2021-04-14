// =====================================================================================
// Number.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>
#include <stdexcept>

#include "Number.h"

// c'tors / d'tor
Number::Number() : m_digits{ 1 } {
    m_digits[0] = 0;
}

Number::Number(std::string_view sv)
{
    std::reverse_iterator<std::string_view::iterator> r = sv.rbegin();

    std::for_each(std::rbegin(sv), std::rend(sv), [this](char ch) {
        if (ch == '.') {
            return;
        }
        else if (!std::isdigit(ch)) {
            throw std::invalid_argument("illegal digit in number");
        }
        else {
            m_digits.push_back(ch - '0');
        }
    });
}

// getter
size_t Number::size() const { return m_digits.size(); }

bool Number::symmetric() const
{
    for (int i = 0; i < m_digits.size() / 2; i++) {
        if (m_digits[i] != m_digits[m_digits.size() - 1 - i])
            return false;
    }

    return true;
}

// public interface
Number Number::add (const Number& number) const
{
    // maximum of number of digits 
    size_t count{ size() >= number.size() ?
        size() + 1 :
        number.size() + 1
    };

    // add numbers digit per digit
    std::vector<int> digits;
    int carry{};
    for (size_t i{}; i != count; i++)
    {
        if (i < size())
            carry += m_digits[i];
        if (i < number.size())
            carry += number.m_digits[i];

        digits.push_back(carry % 10);
        carry /= 10;
    }

    // move result vector into a 'Number' object
    Number tmp{};
    tmp.m_digits = std::move(digits);
    tmp.removeLeadingZeros();
    return tmp;
}

Number Number::reverse() const
{
    std::vector<int> digits{ m_digits };
    std::reverse(std::begin(digits), std::end(digits));

    // move digits vector into a 'Number' object
    Number tmp{};
    tmp.m_digits = std::move(digits);
    tmp.removeLeadingZeros();
    return tmp;
}

// private helper methods
void Number::removeLeadingZeros()
{
    // remove trailing zeros, if any ... using STL algorithms
    std::reverse_iterator<std::vector<int>::iterator> r_it{ std::find_if(
        std::rbegin(m_digits),
        std::rend(m_digits),
        [](int value) { return value != 0; }
    ) };

    m_digits.erase(r_it.base(), std::end(m_digits));
}

// output
std::ostream& operator<< (std::ostream& os, const Number& n)
{
    std::for_each(
        std::rbegin(n.m_digits),
        std::rend(n.m_digits),
        [&, i = n.m_digits.size() - 1](int digit) mutable {
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
