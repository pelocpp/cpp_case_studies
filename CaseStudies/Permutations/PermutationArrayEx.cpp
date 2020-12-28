//// =====================================================================================
//// PermutationArrayEx.cpp
//// =====================================================================================
//
//#include <iostream>
//#include <string>
//#include <vector>
//
//#include "PermutationEx.h"
//#include "PermutationArrayEx.h"
//
//// c'tors
//PermutationArray::PermutationArray(int size)
//{
//    m_array.reserve(size);
//}
//
//// public interface
//void PermutationArray::insert(const Permutation& p)
//{
//    m_array.push_back(p);
//}
//
//void PermutationArray::insertAll(char ch)
//{
//    for (Permutation& p : m_array) {
//        p.insertAtFront(ch);
//    }
//}
//
//// operators
//Permutation PermutationArray::operator[] (int i) const
//{
//    return m_array[i];
//}
//
//// output
//std::ostream& operator<< (std::ostream& os, const PermutationArray& array)
//{
//    for (int i = 0; i < array.count(); i++)
//        os << array.m_array[i] << std::endl;
//
//    os << '[' << array.count() << " permutations]" << std::endl;
//
//    return os;
//}
//
//// =====================================================================================
//// End-of-File
//// =====================================================================================
