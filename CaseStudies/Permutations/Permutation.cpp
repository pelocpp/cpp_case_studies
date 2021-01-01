// =====================================================================================
// Permutation.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Permutation.h"
#include "PermutationIterator.h"

// c'tors
Permutation::Permutation(const std::initializer_list<char>& list) : m_values{ list } {
    std::cout << "c'tor (const std::initializer_list)" << std::endl;
}

Permutation::Permutation(const std::string_view s)
{
    std::cout << "c'tor (const std::string_view)" << std::endl;
    m_values = std::vector<char> (s.begin(), s.end());
}

Permutation::Permutation(const std::vector<char>& values) : m_values{ values } {
    std::cout << "c'tor (const std::vector)" << std::endl;
}

//Permutation::Permutation(const std::initializer_list<char>& list) {
//
//    std::cout << "c'tor (const std::initializer_list)" << std::endl;
//
//    for (char ch : list) {
//        if (std::find(std::begin(m_values), std::end(m_values), ch) != std::end(m_values)) {
//            std::stringstream ss;
//            ss << "Element " << ch << " already in Permutation!";
//            throw std::invalid_argument(ss.str());
//        }
//
//        m_values.push_back(ch);
//    }
//}
//
//Permutation::Permutation(const std::string_view sv)
//{
//    std::cout << "c'tor (const std::string_view)" << std::endl;
//
//    for (char ch : sv) {
//        if (std::find(std::begin(m_values), std::end(m_values), ch) != std::end(m_values)) {
//            std::stringstream ss;
//            ss << "Element " << ch << " already in Permutation!";
//            throw std::invalid_argument(ss.str());
//        }
//
//        m_values.push_back(ch);
//    }
//}
//
//Permutation::Permutation(const std::vector<char>& values) {
//    std::cout << "c'tor (const std::vector)" << std::endl;
//
//    for (char ch : values) {
//        if (std::find(std::begin(m_values), std::end(m_values), ch) != std::end(m_values)) {
//            std::stringstream ss;
//            ss << "Element " << ch << " already in Permutation!";
//            throw std::invalid_argument(ss.str());
//        }
//
//        m_values.push_back(ch);
//    }
//}

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

// iterator support
//PermutationIterator Permutation::begin() const {
//    return PermutationIterator{ 0 };
//}
//
//PermutationIterator Permutation::end() const {
//    return PermutationIterator{ static_cast<int>(m_values.size()) };
//}

PermutationIterator Permutation::begin() const {

    return PermutationIterator (*this, 0);;
}

PermutationIterator Permutation::end() const {
    return PermutationIterator( *this, static_cast<int>(m_values.size()) );
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
