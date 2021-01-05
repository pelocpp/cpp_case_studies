// =====================================================================================
// CollatzIterator.h
// =====================================================================================

#pragma once

#include <iostream>
#include <string>

class CollatzIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = int;
    using difference_type = int;
    using pointer = int*;
    using reference = int&;

private:
    int m_start{ 1 };
    int m_current{ 1 };
    int m_last{ };

public:
    // c'tors
    CollatzIterator() = default;
    CollatzIterator(int start);

    // operators
    int operator*() const;
    CollatzIterator& operator++();
    bool operator!=(const CollatzIterator&) const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
