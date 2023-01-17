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
    Permutation(std::initializer_list<T> list) : m_values{ list } {}

    // getter
    size_t grade() const { return m_values.size(); }

    // public interface
    void insertAtFront(T elem) {
        m_values.insert(m_values.begin(), elem);
    }

    Permutation<T> removeAt(size_t idx) const {
        std::vector<T> tmp{ m_values };
        tmp.erase(tmp.begin() + idx);
        return { std::move(tmp) };
    }

    std::vector<T> getValues() const { return m_values; }

    // operator(s)
    const T& operator[](size_t n) const {
        return m_values[n];
    };

    // iterator support
    typename std::vector<T>::const_iterator begin() { return m_values.begin(); }
    typename std::vector<T>::const_iterator end() { return m_values.end(); }

private:
    Permutation(std::vector<T>&& values) noexcept : m_values{ std::move(values) } {}
};

// user defined literal operator
Permutation<int> operator"" _perm(unsigned long long int);

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
