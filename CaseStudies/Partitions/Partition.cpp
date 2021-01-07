// =====================================================================================
// Partition.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <numeric>

#include "Partition.h"

Partition::Partition(const std::initializer_list<int>& list) 
    : m_numbers{ list.begin(), list.end() }
{
    m_number = std::accumulate(m_numbers.cbegin(), m_numbers.cend(), 0);
}

Partition::Partition(const std::vector<int>& numbers)
    : m_numbers{ numbers.cbegin(), numbers.cend() } 
{
    m_number = std::accumulate(m_numbers.cbegin(), m_numbers.cend(), 0);
}

// getter
std::vector<int> Partition::numbers() const {
    std::vector<int> result;
    result.assign(m_numbers.begin(), m_numbers.end());
    return result;
}

// operators
bool operator==(const Partition& p1, const Partition& p2)
{
    // partitions of different numbers can't be compared
    if (p1.number() != p2.number())
        throw std::invalid_argument(std::string("Partitions don't belong to same number!"));

    // partitions with a different number of summands can't be equal
    if (p1.size() != p2.size())
        return false;

    // compare all summands - sets are  sorted
    return (p1.m_numbers == p2.m_numbers);
}

bool operator<(const Partition& p1, const Partition& p2)
{
    // partitions of different numbers can't be compared
    if (p1.number() != p2.number())
        throw std::invalid_argument(std::string("Partitions don't belong to same number!"));

    std::set<int>::iterator it1 = p1.m_numbers.cbegin();
    std::set<int>::iterator it2 = p2.m_numbers.cbegin();

    while (it1 != p1.m_numbers.cend() && it2 != p2.m_numbers.cend()) {

        if ((*it1) > (*it2))
            return false;
        if ((*it1) < (*it2))
            return true;

        ++it1;
        ++it2;
    }

    return true; // wird das erreicht ?????????????????
}

bool operator>(const Partition& p1, const Partition& p2)
{
    return !(p1 < p2);
}

// output
std::ostream& operator<< (std::ostream& os, const Partition& p)
{
    os << p.m_number << " = ";

    std::set<int>::iterator it = p.m_numbers.cbegin();

    int k = 0;
    while (it != p.m_numbers.cend())
    {
        os << (*it);
        if (k < p.m_numbers.size() - 1)
            os << " + ";

        ++it,  ++k;
    }

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
