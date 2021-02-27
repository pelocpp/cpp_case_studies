// =====================================================================================
// ExamplesCollatzExEx.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <ranges>

#include "CollatzIteratorEx.h"
#include "CollatzSequenceEx.h"

template <class T>
class CollatzViewExEx : public std::ranges::view_interface<CollatzViewExEx<T>> {
public:
    CollatzViewExEx() = default;
    CollatzViewExEx(T start) : m_start(start), m_begin(start), m_end () {}

    auto begin() const { return m_begin; }
    auto end() const { return m_end; }

private:
    T m_start;

    CollatzIteratorEx<T> m_begin;
    CollatzIteratorEx<T> m_end;
};

void Test_Collatz_ExEx()
{
    CollatzViewExEx view{ 7 };

    for (int n : view) {
        std::cout << n << " - ";
    }
    std::cout << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
