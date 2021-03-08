// =====================================================================================
// Soldier.h
// =====================================================================================

#pragma once

// #include <iostream>
//#include <string>

class Soldier
{
private:
    size_t m_number{ 1 };

public:
    // c'tors
    Soldier() = delete;
    Soldier(size_t number) : m_number{ number } {};

    // getter
    size_t getNumber() { return m_number; }

    // operators
    size_t operator()() const { return m_number; };
    //CollatzIterator& operator++();
    //bool operator!=(const CollatzIterator&) const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
