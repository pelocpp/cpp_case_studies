// =====================================================================================
// PartitionSet.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <iomanip> 

#include "Partition.h"
#include "PartitionSet.h"

// c'tors
PartitionSet::PartitionSet(int number) : m_number{ number } {}

// operators
//Partition PartitionSet::operator[] (int i) const
//{
//    return m_partitions[i];
//}

// public interface
// PeLo: Das muss mit einem EMPLACE gehen .. siehe Examples ....
void PartitionSet::insert(const Partition& p) {

    //if (!contains(p))
    //    m_partitions.push_back(p);

    m_partitions.insert(p);
}

std::ostream& operator<< (std::ostream& os, const PartitionSet& set)
{
    int n = 1;
    for (const Partition& p : set.m_partitions) {
        os << std::setw(3) << n << ": " << p << std::endl;
        ++n;
    }

    os << '[' << set.size() << " permutations]" << std::endl;

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
