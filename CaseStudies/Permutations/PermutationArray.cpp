#include <iostream>
#include <string>
#include <vector>

#include "Permutation.h"
#include "PermutationArray.h"
// #include "PermutationCalculator.h"

// c'tors / d'tor
//PermutationArray::PermutationArray()
//{
//    m_size = 0;
//    m_top = 0;
//    m_array = (Permutation*)0;
//}
//

PermutationArray::PermutationArray(int size)
{
    m_array.reserve(size);
}

//
//PermutationArray::PermutationArray(const PermutationArray& a)
//{
//    m_size = a.m_size;
//    m_top = a.m_top;
//
//    m_array = new Permutation[a.m_size];
//    for (int i = 0; i < m_top; i++)
//        m_array[i] = a.m_array[i];
//}
//
//PermutationArray::~PermutationArray()
//{
//    delete[] m_array;
//}


// getter/setter
void PermutationArray::setCapacity(int size) {
    m_array.reserve(size);
}

int PermutationArray::getCapacity() const {
    return static_cast<int>(m_array.capacity());
}


// public interface
void PermutationArray::Insert(const Permutation& p)
{
    m_array.push_back(p);

    //if (m_top == m_size)
    //    return false;

    //m_array[m_top] = p;
    //m_top++;
    //return true;
}

void PermutationArray::InsertAll(char ch)
{
    //for (int i = 0; i < m_top; i++)
    //    m_array[i].Insert(c);

    for (Permutation& p : m_array) {
        p.Insert(ch);
    }
}

// operators
//PermutationArray& PermutationArray::operator= (const PermutationArray& a)
//{
//    if (this == &a)
//        return *this;
//
//    delete[] m_array;
//
//    m_size = a.m_size;
//    m_top = a.m_top;
//    m_array = new Permutation[a.m_size];
//
//    for (int i = 0; i < m_top; i++)
//        m_array[i] = a.m_array[i];
//
//    return *this;
//}

Permutation PermutationArray::operator[] (int i) const
{
    return m_array[i];
}

// output
std::ostream& operator<< (std::ostream& os, const PermutationArray& a)
{
    for (int i = 0; i < a.count(); i++)
        os << a.m_array[i] << std::endl;

    os << '[' << a.count() << " permutations]" << std::endl;

    return os;
}