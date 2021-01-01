// =====================================================================================
// PermutationIterator.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t


#include "Permutation.h"
#include "PermutationIterator.h"
//
//PermutationIterator::PermutationIterator(const Permutation* p, int position) : m_p{ p }, m_i{ position } {}
//
//// copy c'tor
////PermutationIterator::PermutationIterator(const PermutationIterator* it) {
////
////    m_p = it->m_p;
////    m_i = it->m_i;
////}
//
//
////void PermutationIterator::setPermutation(const Permutation& p) const {
////    m_p = p;
////}
//
//char PermutationIterator::operator*() const { return (*m_p)[m_i]; }
//
//// need postfix increment and decrement operator++(int) and operator--(int)
//PermutationIterator PermutationIterator::operator++(int) {
//    PermutationIterator tmp(*this);  // copy
//    operator++();                    // pre-increment
//    return tmp;                      // return old value
//}
//
//PermutationIterator PermutationIterator::operator--(int) {
//    PermutationIterator tmp(*this);  // copy
//    operator--();                    // pre-increment
//    return tmp;                      // return old value
//}
//
//// provide also prefix increment and decrement operators
//// as helpers for their postfix pendants
//PermutationIterator& PermutationIterator::operator++() {
//    ++m_i;
//    return *this;
//}
//
//PermutationIterator& PermutationIterator::operator--() {
//    --m_i;
//    return *this;
//}
//
//// subscript operator
//const char& PermutationIterator::operator[] (int pos) {
//
//    //PermutationIterator tmp(this);
//    //tmp.m_i += pos;
//
//    //return tmp;  // returning reference ???????????????????????????
//
//    return m_p->m_values[m_i + pos];
//}
//
//
//
//
//
//// comparison operators
//bool PermutationIterator::operator!=(const PermutationIterator& other) const {
//    return m_i != other.m_i;
//}
//
//bool PermutationIterator::operator==(const PermutationIterator& other) const {
//    return !(*this != other);
//}
//
//
//char PermutationIterator::operator-(const PermutationIterator& other) {
//    // return *(m_p[m_i]) - *(other.m_p[m_i]);
//    return 1;
//}

// =====================================================================================
// End-of-File
// =====================================================================================




PermutationIterator::PermutationIterator(const Permutation& p, int position) : m_p{ p }, m_i{ position } {}

// copy c'tor
//PermutationIterator::PermutationIterator(const PermutationIterator* it) {
//
//    m_p = it->m_p;
//    m_i = it->m_i;
//}


//void PermutationIterator::setPermutation(const Permutation& p) const {
//    m_p = p;
//}

char PermutationIterator::operator*() const { return m_p[m_i]; }

// need postfix increment and decrement operator++(int) and operator--(int)
PermutationIterator PermutationIterator::operator++(int) {
    PermutationIterator tmp(*this);  // copy
    operator++();                    // pre-increment
    return tmp;                      // return old value
}

PermutationIterator PermutationIterator::operator--(int) {
    PermutationIterator tmp(*this);  // copy
    operator--();                    // pre-increment
    return tmp;                      // return old value
}

// provide also prefix increment and decrement operators
// as helpers for their postfix pendants
PermutationIterator& PermutationIterator::operator++() {
    ++m_i;
    return *this;
}

PermutationIterator& PermutationIterator::operator--() {
    --m_i;
    return *this;
}

// subscript operator
const char& PermutationIterator::operator[] (long pos) const {

    // return m_p.m_values[m_i + pos];

    return m_p.m_values[0];
}

//char& PermutationIterator::operator[] (long pos) {
//
//    return m_p.m_values[m_i + pos];
//}


// comparison operators
bool PermutationIterator::operator!=(const PermutationIterator& other) const {
    return m_i != other.m_i;
}

bool PermutationIterator::operator==(const PermutationIterator& other) const {
    return !(*this != other);
}



//char PermutationIterator::operator-(const PermutationIterator& other) {
//    // return *(m_p[m_i]) - *(other.m_p[m_i]);
//    return 1;
//}

