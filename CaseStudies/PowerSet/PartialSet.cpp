// =====================================================================================
// PartialSet.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

#include "PartialSet.h"

// c'tors / d'tor
PartialSet::PartialSet(const std::initializer_list<size_t>& list)
    : m_numbers{ list.begin(), list.end() } {}

// public operators
bool operator== (const PartialSet& set1, const PartialSet& set2)
{
    // delegating comparison to standard comparison of two std::set objects
    return (set1.m_numbers == set2.m_numbers);
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
}

// output
std::ostream& operator<< (std::ostream& os, const PartialSet& set)
{
    os << "{ ";
    if (set.m_numbers.begin() != set.m_numbers.end()) {

        std::set<size_t>::const_iterator it{ set.m_numbers.begin() };
        std::set<size_t>::const_iterator penultimate{ std::prev(set.m_numbers.end()) };
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
