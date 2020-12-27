#include <iostream>
using namespace std;

#include "Permutation.h"
#include "PermutationArray.h"
#include "PermutationCalculator.h"

// c'tors / d'tor
PermutationArray::PermutationArray()
{
    m_size = 0;
    m_top = 0;
    m_array = (Permutation*)0;
}

PermutationArray::PermutationArray(int size)
{
    m_size = size;
    m_top = 0;
    m_array = new Permutation[size];
}

PermutationArray::PermutationArray(const PermutationArray& a)
{
    m_size = a.m_size;
    m_top = a.m_top;

    m_array = new Permutation[a.m_size];
    for (int i = 0; i < m_top; i++)
        m_array[i] = a.m_array[i];
}

PermutationArray::~PermutationArray()
{
    delete[] m_array;
}

// public interface
bool PermutationArray::Insert(const Permutation& p)
{
    if (m_top == m_size)
        return false;

    m_array[m_top] = p;
    m_top++;
    return true;
}

void PermutationArray::InsertAll(char c)
{
    for (int i = 0; i < m_top; i++)
        m_array[i].Insert(c);
}

// operators
PermutationArray& PermutationArray::operator= (const PermutationArray& a)
{
    if (this == &a)
        return *this;

    delete[] m_array;

    m_size = a.m_size;
    m_top = a.m_top;
    m_array = new Permutation[a.m_size];

    for (int i = 0; i < m_top; i++)
        m_array[i] = a.m_array[i];

    return *this;
}

Permutation PermutationArray::operator[] (int i) const
{
    return m_array[i];
}

// output
ostream& operator<< (ostream& os, const PermutationArray& a)
{
    for (int i = 0; i < a.m_size; i++)
        os << a.m_array[i] << endl;

    os << '[' << a.m_top << " permutations]" << endl;

    return os;
}