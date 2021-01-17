// =====================================================================================
// PartialSet.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>

#include "PartialSet.h"
#include <algorithm>

// c'tors / d'tor
PartialSet::PartialSet(const std::initializer_list<int>& list)
    : m_numbers{ list.begin(), list.end() } {}

// public operators
bool operator== (const PartialSet& set1, const PartialSet& set2)
{
    // partial sets with a different count of numbers can't be equal
    if (set1.size() != set2.size())
        return false;

    // compare all numbers - partial sets are sorted
    return (set1.m_numbers == set2.m_numbers);
}

bool operator!= (const PartialSet& s1, const PartialSet& s2)
{
	return !(s1 == s2);
}

bool operator< (const PartialSet& set1, const PartialSet& set2)
{
    if (set1.m_numbers.size() < set2.m_numbers.size()) {
        return true;
    }
    else if (set1.m_numbers.size() > set2.m_numbers.size()) {
        return false;
    }
    else {
        // use default function object std::less<int>
        return set1.m_numbers < set2.m_numbers;
    }

    // return set1.m_numbers < set2.m_numbers;
}

// output
std::ostream& operator<< (std::ostream& os, const PartialSet& set)
{
    os << "{ ";
    if (set.m_numbers.begin() != set.m_numbers.end()) {

        std::set<int>::const_iterator it = set.m_numbers.begin();
        std::set<int>::const_iterator penultimate = std::prev(set.m_numbers.end());
        for (it = set.m_numbers.begin(); it != penultimate; ++it) {
            os << (*it) << ", ";
        }
        os << (*penultimate) << ' ';
    }
    os << "}";
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
