// =====================================================================================
// PermutationContainer.h
// =====================================================================================

#pragma once

#include <iostream>
#include <string>
#include <list>

#include "Permutation.h"

template <typename T>
class PermutationContainer
{
private:
    std::list<Permutation<T>> m_container;

public:
    // c'tors/d'tor
    PermutationContainer() = default;

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

    // iterator support
    typename std::list<Permutation<T>>::iterator begin() { return m_container.begin(); }
    typename std::list<Permutation<T>>::iterator end() { return m_container.end(); }
    typename std::list<Permutation<T>>::const_iterator begin() const { return m_container.cbegin(); }
    typename std::list<Permutation<T>>::const_iterator end() const { return m_container.cend(); }
};

template <typename T>
inline std::ostream& operator<< (std::ostream& os, const PermutationContainer<T>& container) {

    for (const auto& perm : container) {
        os << perm << std::endl;
    }
    os << '[' << container.count() << " permutations]" << std::endl;

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
