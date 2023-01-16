// =====================================================================================
// Permutation.h
// =====================================================================================

#pragma once

#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Permutation
{
private:
    std::vector<T> m_values;

public:
    // c'tors
    Permutation() = default;
    Permutation(const std::initializer_list<T> list) : m_values{ list } {}

    // getter
    size_t grade() const { return m_values.size(); }

    // public interface
    void insertAtFront(T ch) {
        m_values.insert(m_values.begin(), ch);
    }

    Permutation<T> removeAt(size_t i) const {
        std::vector<T> tmp{ m_values };
        tmp.erase(tmp.begin() + i);
        return { std::move(tmp) };
    }

    // operator(s)
    const T& operator[](size_t n) const {
        return m_values[n];
    };

    // iterator support
    typename std::vector<T>::iterator begin() { return m_values.begin(); }
    typename std::vector<T>::iterator end() { return m_values.end(); }


private:
    Permutation(const std::vector<T>&& values) : m_values{ std::move(values) } {}
};


template <typename T>
inline std::ostream& operator<< (std::ostream& os, const Permutation<T>& p) {
    os << '[';
    for (size_t i{}; i != p.grade(); ++i)
    {
        os << p[i];
        if (i < p.grade() - 1)
            os << ',';

    }
    os << ']';
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
