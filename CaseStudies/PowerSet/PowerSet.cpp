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


// c'tors / d'tor
PowerSet::PowerSet(int size) : m_size{ size }, m_cardinality{ powerByTwo(size) }
{
    computePartialSets();
}

void PowerSet::computePartialSets() {

    // m_sets.resize(m_cardinality);

    //std::generate(
    //    std::begin(m_sets), 
    //    std::end(m_sets), 
    //    [this, i = 0] () mutable { 

    //        PartialSet set{ };
    //        for (int j = 0; j < m_size; j++) {
    //            int mask = 1 << j;
    //            if ((mask & i) != 0) {
    //                set.add(j + 1);
    //            }
    //        }

    //        ++i;
    //        return set;
    //    });

    for (int i = 0; i < m_cardinality; i++) {

        PartialSet set{ };
        for (int j = 0; j < m_size; j++) {

            int mask = 1 << j;
            if ((mask & i) != 0) {
                set.add(j + 1);
            }
        }

        m_sets.insert(set);
    }
}





// public interface

//
//int PowerSet::PartialSetsBySize (int size)
//{
//    // count number of partial sets with specified cardinality
//    int count = 0;
//
//    Reset();
//    while (MoveNext())
//    {
//        PartialSet set = Current();
//        if (set.GetSize() == size)
//            count ++;
//    }
//
//    return count;
//}
//
//void PowerSet::PartialSetsBySize (int size, PartialSet buf[], int len)
//{
//    int count = 0;
//    Reset();
//    while (MoveNext())
//    {
//        PartialSet set = Current();
//        if (set.GetSize() == size)
//        {
//            if (count < len) // guard
//            {
//                buf[count] = set;
//                count ++;
//            }
//        }
//    }
//}
//

//
//PartialSet PowerSet::operator[] (int index)
//{
//    return *m_sets[index];
//}
//
//// enumerator interface
//void PowerSet::Reset()
//{
//    m_index = -1;
//}
//
//bool PowerSet::MoveNext()
//{
//    m_index ++;
//    if (m_index < m_cardinality)
//    {
//        return true;
//    }
//    else
//    {
//        Reset();
//        return false;
//    }
//}
//
//PartialSet PowerSet::Current()
//{
//    return *m_sets[m_index];
//}
//


// input/output
std::ostream& operator<< (std::ostream& os, const PowerSet& ps)
{
    for (const auto& set : ps.m_sets) {
        os << set << std::endl;
    }

    return os;
}

// private helper methods
int PowerSet::powerByTwo(int num)
{
    int base_2;
    for (base_2 = 1; base_2 < (1 << num); base_2 <<= 1)
        ;

    return base_2;
}

// =====================================================================================
// End-of-File
// =====================================================================================
