// =====================================================================================
// CollatzIteratorEx.h
// =====================================================================================

#pragma once

#include <iostream>
#include <string>

template <typename T>  
class CollatzIteratorEx
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = T;
    using pointer = T*;
    using reference = T&;

private:
    T m_start{};
    T m_last{};
    T m_current{};

public:
    // c'tors
    CollatzIteratorEx() : m_start{ T{ 1 } }, m_current{ T{ 1 } } {}
    CollatzIteratorEx(T start) : m_start{ start }, m_current{ start } {}

    // operators
    T operator*() const { return m_current; }

    CollatzIteratorEx& operator++() {

        m_last = m_current;

        m_current = (m_current % 2 == 0)
            ? m_current = m_current / 2
            : m_current = 3 * m_current + 1;

        return *this;
    }

    bool operator!=(const CollatzIteratorEx& seq) const
    {
        return m_last != seq.m_current;
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
