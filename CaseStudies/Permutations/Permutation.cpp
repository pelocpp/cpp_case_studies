// =====================================================================================
// Permutation.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

#include "Permutation.h"

// c'tors
Permutation::Permutation(const std::vector<char>& values) : m_values{ values }{}

Permutation::Permutation(const std::string_view s)
{
    std::cout << "c'tor (const std::string_view)" << std::endl;
    m_values = std::vector<char> (s.begin(), s.end());
}

// public interface
void Permutation::insertAtFront(char ch)
{
    m_values.insert(m_values.begin(), ch);
}

Permutation Permutation::removeAt(int i) const
{
    std::vector<char> tmp = m_values;
    tmp.erase(tmp.begin() + i);
    return Permutation(tmp);
}

// operator(s)
char Permutation::operator[] (int i) const
{
    return m_values[i];
}

// output
std::ostream& operator<< (std::ostream& os, const Permutation& p)
{
    os << '[';
    for (int i = 0; i < p.m_values.size(); i++)
    {
        os << p.m_values[i];
        if (i < p.m_values.size() - 1)
            os << ',';

    }
    os << ']';
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
