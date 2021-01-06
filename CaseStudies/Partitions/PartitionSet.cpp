// =====================================================================================
// PartitionSet.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <functional>
#include <vector>
#include <iomanip> 

#include "Partition.h"
#include "PartitionSet.h"

// c'tors
PartitionSet::PartitionSet(int number) : m_number{ number } {}

// public interface
// PeLo: Das muss mit einem EMPLACE gehen .. siehe Examples ....
void PartitionSet::insert(const Partition& p) {

    m_partitions.insert(p);
}

// https://docs.w3cub.com/cpp/container/set/emplace

void PartitionSet::emplace()
{
    m_partitions.emplace<Partition>({ 1, 2, 3 });
}

//template <typename ... Args>
//void PartitionSet::emplace2(Args&& ... args)
//{
//    std::pair<std::set<Partition, std::greater<Partition>>::iterator, bool> result = m_partitions.emplace(std::initializer_list<int> { args ... });
//    std::cout << std::boolalpha << "Result: " << std::get<1>(result) << std::endl;
//}
//


// output
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
