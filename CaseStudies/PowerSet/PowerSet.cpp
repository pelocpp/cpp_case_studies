// =====================================================================================
// PowerSet.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "PartialSet.h"
#include "PowerSet.h"


//
//// c'tors / d'tor
//PowerSet::PowerSet ()
//{
//    m_cardinality = 1;
//    m_sets = new PartialSet*[1];
//    m_sets[0] = new PartialSet;
//}
//
//PowerSet::PowerSet (const PowerSet& ps)
//{
//    m_elements = ps.m_elements;
//    m_cardinality = ps.m_cardinality;
//    m_index = -1;
//
//    m_sets = new PartialSet*[m_cardinality];
//    for (int i = 0; i < m_cardinality; i++)
//    {
//        m_sets[i] = new PartialSet(*ps.m_sets[i]);
//    }
//}
//



PowerSet::PowerSet(int size) : m_size{ size }, m_cardinality{ powerByTwo(size) }
{
    computePartialSets();
}


void PowerSet::computePartialSets() {

    for (int i = 0; i < m_cardinality; i++) {

        PartialSet set{ };
        for (int j = 0; j < m_size; j++) {

            int mask = 1 << j;
            if ((mask & i) != 0) {
                set.add(j + 1);
            }
        }

        m_sets.push_back(set);
    }
}


//PowerSet::PowerSet (int elements)
//{
//    m_cardinality = PowerSet::PowerByTwo (elements);
//
//    m_sets = new PartialSet*[m_cardinality];
//
//    for (int i = 0; i < m_cardinality; i++)
//    {
//        // calculate number of elements in i.th partial set
//        int num = 0;
//        for (int j = i; j != 0; j = j / 2)
//        {
//            if (j % 2 == 1)
//                num ++;
//        }
//
//        // compute i.th partial set
//        int* set = new int[num];
//        int index = 0;
//        for (int j = 0; j < elements; j ++)
//        {
//            int mask = 1 << j;
//            if ((mask & i) != 0)
//            {
//                set[index] = j + 1;
//                index++;
//            }
//        }
//
//        PartialSet* ps = new PartialSet(set, num);
//        delete[] set;
//
//        m_sets[i] = ps;
//    }
//}


//
//// public interface
//void PowerSet::Sort ()
//{
//    for (int i = m_cardinality - 1; i >= 0; i --)
//    {
//        for (int j = 0; j < i; j ++)
//        {
//            if (*m_sets[j+1] <= *m_sets[j])
//            {
//                PartialSet* tmp = m_sets[j+1];
//                m_sets[j+1] = m_sets[j];
//                m_sets[j] = tmp;
//            }
//        }
//    }
//}
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
    for (int i = 0; i < ps.m_cardinality; i++)
        os << ps.m_sets[i] << "\n";
 
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
