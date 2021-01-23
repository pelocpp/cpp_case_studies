// =====================================================================================
// PartitionSet.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <numeric>
#include <iomanip> 

#include "Partition.h"
#include "PartitionSet.h"
#include <algorithm>

// c'tors
PartitionSet::PartitionSet(size_t number) : m_number{ number } {}

// public interface
bool PartitionSet::insert(const Partition& p) {

    if (p.number() != m_number) {
        throw std::invalid_argument("Number of partition doesn't match set!");
    }

    std::pair<std::set<Partition, std::greater<Partition>>::iterator, bool> result = m_partitions.insert(p);
    return std::get<1>(result);
}

// output
std::ostream& operator<< (std::ostream& os, const PartitionSet& set)
{
    std::for_each(
        std::begin(set.m_partitions), 
        std::end(set.m_partitions),
        [&, n = 1](const Partition& p) mutable {
            os << std::setw(3) << n << ": " << p << std::endl;
            ++n;
        }
    );
    os << '[' << set.size() << " partitions]" << std::endl;
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
