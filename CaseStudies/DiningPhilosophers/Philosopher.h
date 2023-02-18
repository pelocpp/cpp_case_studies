// ===========================================================================
// class Philosopher
// ===========================================================================

#pragma once

#include <mutex>
#include <future>
#include <random>


#include "Table.h"
#include "Philosopher.h"
#include "Table.h"
#include "Table.h"


class Philosopher {
private:
    // dining philosophers utilities
    Table& m_table;
    int m_seat;
    PhilosopherState m_state;
    int m_activities;

    // random utilities
    static std::random_device device;
    static std::mt19937 generator;
    static std::uniform_int_distribution<int> distribution;

    // threading utils
    std::future<void> m_future;
    bool m_running;

public:
    // c'tor
    Philosopher(Table& table, int seat);

    // public interface
    void start();
    void stop();

private:
    // private helper methods
    void run();
    void thinking();
    void hungry();
    void eating();
    void eatingDone();
};

class PhilosopherEx {
private:
    // dining philosophers utilities
    std::string const name;
    TableEx const& dinnertable;
    //ForkEx& left_fork;
    //ForkEx& right_fork;

    std::thread       lifethread;
    std::mt19937      rng{ std::random_device{}() };


public:
    // c'tor
    PhilosopherEx(Table& table, int seat);

    // public interface
    void start();
    void stop();

private:
    // private helper methods
    void dine();
    void run();
    void thinking();
    void hungry();
    void eating();
    void eatingDone();
};

// ===========================================================================
// End-of-File
// ===========================================================================
