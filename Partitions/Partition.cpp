// =====================================================================================
// Partition.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
//#include <sstream>

#include "Partition.h"

// #include "PermutationIterator.h"

Partition::Partition(const std::initializer_list<int>& list) : m_numbers{ list } {
    // PeLo TODO muss hier sortiert werden ............. JA
   // std::cout << "c'tor (const std::initializer_list)" << std::endl;
    std::sort(std::begin(m_numbers), std::end(m_numbers));

    m_number = std::accumulate(m_numbers.begin(), m_numbers.end(), 0);
}

// operators
bool operator==(const Partition& p1, const Partition& p2)
{
    // TODO PeLo  : Hier müssen exception hin .... wenn die numbers verschiend sind !!!!

    // partitions of different numbers can't be equal
    if (p1.number() != p2.number())
        return false;

    // partitions with a different number of summands can't be equal
    if (p1.size() != p2.size())
        return false;

    // compare all summands - implementation assumes sorted vectors
    for (int i = 0; i < p1.m_numbers.size(); i++) {
        if (p1.m_numbers[i] != p2.m_numbers[i])
            return false;
    }

    return true;
}

// output
std::ostream& operator<< (std::ostream& os, const Partition& p)
{
    os << p.m_number << " = ";

    for (int i = 0; i < p.m_numbers.size(); i++)
    {
        os << p.m_numbers[i];
        if (i < p.m_numbers.size() - 1)
            os << " + ";

    }
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
