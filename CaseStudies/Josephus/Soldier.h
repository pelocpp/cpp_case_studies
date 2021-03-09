// =====================================================================================
// Soldier.h
// =====================================================================================

#pragma once

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
};

// =====================================================================================
// End-of-File
// =====================================================================================
