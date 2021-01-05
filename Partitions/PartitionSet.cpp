// =====================================================================================
// PartitionSet.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>

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

bool PartitionSet::contains(const Partition& p) {

    return false;
}

std::ostream& operator<< (std::ostream& os, const PartitionSet& set)
{
    //for (int i = 0; i < set.size(); i++)
    //    os << set.m_partitions[i] << std::endl;

    for (const Partition& p : set.m_partitions) {
        os << p << std::endl;
    }

    os << '[' << set.size() << " permutations]" << std::endl;

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
