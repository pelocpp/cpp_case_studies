// ===========================================================================
// Philosopher.h
// ===========================================================================

#pragma once


#include <future>

#include "Table.h"
#include "Philosopher.h"

class Philosopher
{
private:
    std::string       m_name;
    Table&            m_table;
    size_t            m_seat;   // 0 .. 4

    // threading utils
    std::future<void> m_lifeThread;
    bool              m_running;

public:
    // user-defined c'tor
    Philosopher(std::string_view name, Table& table, size_t seat);

    // public interface
    void start();
    void stop();
    void dine() const;
    void eating() const;
    void eatingDone() const;
    void thinking() const;
    void hungry() const;
};

// ===========================================================================
// End-of-File
// ===========================================================================
