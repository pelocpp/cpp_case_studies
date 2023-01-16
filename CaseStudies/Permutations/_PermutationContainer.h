// =====================================================================================
// PermutationContainer.h
// =====================================================================================

#pragma once

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "_Permutation.h"

template <typename T>
class PermutationContainer
{
private:
    std::vector<PermutationExEx<T>> m_container;

public:
    // c'tors/d'tor
    PermutationContainer() = default;

    PermutationContainer(size_t size) {
        m_container.reserve(size);
    }

    // getter
    size_t count() const { return m_container.size(); }

    // public interface
    void insert(const PermutationExEx<T>& p) {
        m_container.push_back(p);
    }

    // TODO: Das && ist falsch !!!!!
    // WO WIRD DAS BENÖTIGT
    //void emplace(std::initializer_list<char> list) noexcept {
    //    m_container.emplace_back(list);
    //}

    void insertAll(T elem) {
        for (PermutationExEx<T>& p : m_container) {
            p.insertAtFront(elem);
        }
    }

    // operator(s)
    PermutationExEx<T> operator[] (size_t i) const {
        return m_container[i];
    }

    // iterator support
    typename std::vector<PermutationExEx<T>>::iterator begin() { return m_container.begin(); }
    typename std::vector<PermutationExEx<T>>::iterator end() { return m_container.end(); }

};

template <typename T>
inline std::ostream& operator<< (std::ostream& os, const PermutationContainer<T>& array) {
    for (int i = 0; i < array.count(); i++)
        os << array[i] << std::endl;

    os << '[' << array.count() << " permutations]" << std::endl;

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
