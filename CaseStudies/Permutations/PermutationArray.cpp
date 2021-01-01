// =====================================================================================
// PermutationArray.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

#include "Permutation.h"
#include "PermutationArray.h"
#include "PermutationIterator.h"

// c'tors
PermutationArray::PermutationArray(int size)
{
    m_array.reserve(size);
}

// public interface
void PermutationArray::insert(const Permutation& p)
{
    std::cout << "insert (1)" << std::endl;
    m_array.push_back(p);
}

void PermutationArray::emplace(std::string_view&& s) noexcept
{
    std::cout << "emplace (1)" << std::endl;
    m_array.emplace_back(s);
}

void PermutationArray::emplace(std::initializer_list<char>&& list) noexcept
{
    std::cout << "emplace (2)" << std::endl;
    m_array.emplace_back(list);
}


void PermutationArray::insertAll(char ch)
{
    for (Permutation& p : m_array) {
        p.insertAtFront(ch);
    }
}

// operators
Permutation PermutationArray::operator[] (int i) const
{
    return m_array[i];
}

// output
std::ostream& operator<< (std::ostream& os, const PermutationArray& array)
{
    for (int i = 0; i < array.count(); i++)
        os << array.m_array[i] << std::endl;

    os << '[' << array.count() << " permutations]" << std::endl;

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
