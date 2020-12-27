#include <iostream>
#include <string>
#include <vector>

#include "Permutation.h"

// c'tors / d'tor
//Permutation::Permutation()
//{
//    m_values = (char*)0;
//    m_length = 0;
//}

Permutation::Permutation(const std::vector<char> values)
{
    m_values = values;
}

Permutation::Permutation(const std::string_view s)
{
    m_values = std::vector<char> (s.begin(), s.end());
}

//Permutation::Permutation(char values[], int length)
//{
//    m_values = new char[length];
//    for (int i = 0; i < length; i++)
//        m_values[i] = values[i];
//    m_length = length;
//}
//
//Permutation::Permutation(const Permutation& p)
//{
//    m_values = new char[p.m_length];
//    for (int i = 0; i < p.m_length; i++)
//        m_values[i] = p.m_values[i];
//    m_length = p.m_length;
//}

//Permutation::~Permutation()
//{
//    delete[] m_values;
//}

// public interface
void Permutation::Insert(char ch)
{
    m_values.insert(m_values.begin(), ch);

    //// allocate temporary buffer
    //char* tmp = new char[m_length + 1];

    //// insert 'c' at first position
    //tmp[0] = c;

    //// copy current permutation to the end
    //for (int i = 0; i < m_length; i++)
    //    tmp[i + 1] = m_values[i];

    //// switch to new buffer
    //m_length++;
    //delete[] m_values;
    //m_values = tmp;
}

Permutation Permutation::Remove(int i) const
{
    std::vector<char> tmp = m_values;

    tmp.erase(tmp.begin() + i);

    return Permutation(tmp);

    //// allocate temporary buffer
    //char* tmp = new char[m_length - 1];

    //// copy current permutation without i.-th element
    //for (int j = 0; j < i; j++)
    //    tmp[j] = m_values[j];
    //for (int j = i + 1; j < m_length; j++)
    //    tmp[j - 1] = m_values[j];

    //return Permutation(tmp, m_length - 1);
}

// operators
//Permutation& Permutation::operator= (const Permutation& p)
//{
//    if (this == &p)
//        return *this;
//
//    delete[] m_values;
//    m_values = new char[p.m_length];
//
//    for (int i = 0; i < p.m_length; i++)
//        m_values[i] = p.m_values[i];
//    m_length = p.m_length;
//
//    return *this;
//}

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