// =====================================================================================
// PermutationContainer.h
// =====================================================================================

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Permutation.h"

template <typename T>
class PermutationContainer
{
private:
    std::vector<Permutation<T>> m_container;

public:
    // c'tors/d'tor
    PermutationContainer() = default;

    PermutationContainer(size_t size) {
        m_container.reserve(size);
    }

    // getter
    size_t count() const { return m_container.size(); }

    // public interface
    void insert(const Permutation<T>& p) {
        m_container.push_back(p);
    }

    void insertAll(T elem) {
        for (Permutation<T>& p : m_container) {
            p.insertAtFront(elem);
        }
    }

    // operator(s)
    Permutation<T> operator[] (size_t i) const {
        return m_container[i];
    }

    // iterator support
    typename std::vector<Permutation<T>>::iterator begin() { return m_container.begin(); }
    typename std::vector<Permutation<T>>::iterator end() { return m_container.end(); }

};

template <typename T>
inline std::ostream& operator<< (std::ostream& os, const PermutationContainer<T>& array) {
    for (size_t i{}; i != array.count(); ++i)
        os << array[i] << std::endl;

    os << '[' << array.count() << " permutations]" << std::endl;

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
