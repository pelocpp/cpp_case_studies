// =====================================================================================
// PartialSet.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>

#include "PartialSet.h"

// c'tors / d'tor
PartialSet::PartialSet(const std::initializer_list<int>& list)
    : m_numbers{ list.begin(), list.end() } {}
   

// public interface
//bool PartialSet::isEqual (const PartialSet& set) const
//{
//    //if (m_size != set.m_size)
//    //    return false;
//
//    //for (int i = 0; i < m_size; i++)
//    //{
//    //    if (m_numbers[i] != set.m_numbers[i])
//    //        return false;
//    //}
//
//    //return true;
//
//    // partitions of different numbers can't be compared
//    if (p1.number() != p2.number())
//        throw std::invalid_argument(std::string("Partitions don't belong to same number!"));
//
//    // partitions with a different number of summands can't be equal
//    if (p1.size() != p2.size())
//        return false;
//
//    // compare all summands - sets are  sorted
//    return (p1.m_numbers == p2.m_numbers);
//}

//bool PartialSet::IsLessThan (const PartialSet& set) const
//{
//    if (m_size < set.m_size)
//    {
//        return true;
//    }
//    else if (m_size > set.m_size)
//    {
//        return false;
//    }
//    else
//    {
//        for (int i = 0; i < m_size; i++)
//        {
//            if (m_numbers[i] < set.m_numbers[i])
//                return true;
//            else if (m_numbers[i] > set.m_numbers[i])
//                return false;
//            else
//                continue;
//        }
//    }
//
//    return true;
//}
//
//bool PartialSet::IsGreaterThan (const PartialSet& set) const
//{
//	if (this -> IsEqual (set))
//		return true;
//
//	return ! this -> IsLessThan (set);
//}

// public operators
//bool operator== (const PartialSet& set1, const PartialSet& set2)
//{
//    // partial sets with a different count of numbers can't be equal
//    if (set1.size() != set2.size())
//        return false;
//
//    // compare all numbers - partial sets are sorted
//    return (set1.m_numbers == set2.m_numbers);
//}
//
//bool operator!= (const PartialSet& s1, const PartialSet& s2)
//{
//	return !(s1 == s2);
//}
//
//bool operator<= (const PartialSet& set1, const PartialSet& set2)
//{
//    if (set1.m_numbers.size() < set2.m_numbers.size())
//    {
//        return true;
//    }
//    else if (set1.m_numbers.size() > set2.m_numbers.size())
//    {
//        return false;
//    }
//    else
//    {
//
//        // TODO: das muss doch gehen, oder ??
//        return set1.m_numbers <= set2.m_numbers;
//
//        //for (int i = 0; i < m_size; i++)
//        //{
//        //    if (m_numbers[i] < set.m_numbers[i])
//        //        return true;
//        //    else if (m_numbers[i] > set.m_numbers[i])
//        //        return false;
//        //    else
//        //        continue;
//        //}
//    }
//}
//
//bool operator>= (const PartialSet& set1, const PartialSet& set2)
//{
//	// return set1.IsGreaterThan (set2);
//
//    return true;
//}

// input/output
std::ostream& operator<< (std::ostream& os, const PartialSet& set)
{
    os << "{ ";

    int k = 0;
    std::set<int>::iterator it = set.m_numbers.cbegin();
    while (it != set.m_numbers.cend())
    {
        os << (*it);
        if (k < set.m_numbers.size() - 1)
            os << ", ";

        ++it, ++k;
    }

    os << " }";
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
