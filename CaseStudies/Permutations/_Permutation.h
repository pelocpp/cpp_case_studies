// =====================================================================================
// PermutationExEx.h
// =====================================================================================

#pragma once

#include <iostream>
#include <string>
#include <vector>

// primary template
template <typename T>
class PermutationExEx
{
private:
    std::vector<T> m_values;

public:
    // c'tors
    PermutationExEx() = default;
    PermutationExEx(const std::initializer_list<T> list) : m_values{ list } {}

    // getter
    size_t grade() const { return m_values.size(); }

    // public interface
    void insertAtFront(T ch) {
        m_values.insert(m_values.begin(), ch);
    }

    PermutationExEx<T> removeAt(size_t i) const {
        std::vector<T> tmp = m_values;
        tmp.erase(tmp.begin() + i);
        // return PermutationExEx<T>(tmp);   // andere Schreibweise {  }
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
    PermutationExEx(const std::vector<T>&& values) : m_values{ std::move(values) } {}
};


template <typename T>
inline std::ostream& operator<< (std::ostream& os, const PermutationExEx<T>& p) {
    os << '[';
    for (int i = 0; i < p.grade(); i++)
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


//// full template specialization
//template <>
//class PermutationExEx<std::string>
//{
//private:
//    std::vector<char> m_values;
//
//   //friend PermutationExEx<char>(const std::vector<char>&& values);
//
//    // template <typename> friend class PermutationExEx;
//
//    friend class PermutationExEx<char>;
//
//public:
//    // c'tors
//    PermutationExEx() = default;
//    PermutationExEx(const std::string& list) {  } // TBD
//
//    // getter
//    size_t grade() const { return m_values.size(); }
//
//    // public interface
//    void insertAtFront(char ch) {
//        m_values.insert(m_values.begin(), ch);
//    }
//
//    PermutationExEx<char> removeAt(size_t i) const {
//        std::vector<char> tmp = m_values;
//        tmp.erase(tmp.begin() + i);
//        // return PermutationExEx<T>(tmp);   // andere Schreibweise {  }
//        return { std::move(tmp) };
//    }
//
//    // operator(s)
//    const char& operator[](size_t n) const {
//        return m_values[n];
//    };
//
//    // iterator support
//    typename std::vector<char>::iterator begin() { return m_values.begin(); }
//    typename std::vector<char>::iterator end() { return m_values.end(); }
//
//
//private:
//    PermutationExEx(const std::vector<char>&& values) : m_values{ std::move(values) } {}
//};
