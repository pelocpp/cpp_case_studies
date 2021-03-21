// =====================================================================================
// PowerSet.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "PartialSet.h"
#include "PowerSet.h"

// c'tors
PowerSet::PowerSet() : m_size{ 0 }, m_cardinality{ 1 }, m_sets{ PartialSet {} } {}

PowerSet::PowerSet(size_t size) : m_size{ size }, m_cardinality{ powerByTwo(size) }
{
    computePartialSets();
}

// public interface
PowerSet PowerSet::partialSetsBySize(size_t size) {

    PowerSet result{ };
    result.m_sets.clear();
    for (const PartialSet& set : m_sets) {
        if (set.size() == size) {
            result.m_sets.insert(set);
        }
    }
    
    return result;
}

// iterator support
std::set<PartialSet>::const_iterator PowerSet::begin() { 
    return m_sets.cbegin();
}

std::set<PartialSet>::const_iterator PowerSet::end() {
    return m_sets.cend(); 
}

// output
std::ostream& operator<< (std::ostream& os, const PowerSet& ps)
{
    for (const auto& set : ps.m_sets) {
        os << set << std::endl;
    }

    return os;
}

// private helper methods
void PowerSet::computePartialSets() {

    for (size_t i{}; i != m_cardinality; i++) {

        PartialSet set{ };
        for (size_t j{}; j != m_size; j++) {

            int mask = 1 << j;
            if ((mask & i) != 0) {
                set.add(j + 1);
            }
        }

        m_sets.insert(set);
    }
}

size_t PowerSet::powerByTwo(size_t num)
{
    size_t base_2;
    for (base_2 = 1; base_2 < (static_cast<size_t>(1) << num); base_2 <<= 1)
        ;

    return base_2;
}

// =====================================================================================
// End-of-File
// =====================================================================================
