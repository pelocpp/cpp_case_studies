// ===========================================================================
// Philosopher.cpp
// ===========================================================================

#include <array>
#include <future>
#include <string_view>
#include <cassert>

#include "Logger.h"
#include "DiningPhilosophers.h"
#include "Random.h"
#include "Table.h"
#include "Philosopher.h"

Philosopher::Philosopher(std::string_view name, Table& table, size_t seat) :
    m_name{ name },
    m_table{ table },
    m_seat{ seat },
    m_running{ false }
{}

void Philosopher::start()
{
    m_running = true;
    m_lifeThread = std::async(
        std::launch::async, [this]() { dine(); }
    );
}

void Philosopher::stop()
{
    m_running = false;
    m_lifeThread.get();
}

void Philosopher::dine() const
{
    std::thread::id philosopherThreadId{ std::this_thread::get_id() };
    Logger::logAbs(std::cout, m_name, " enters room [", philosopherThreadId, ']');

    while (m_running) {
        thinking();
        hungry();
        eating();
        eatingDone();
    }

    Logger::logAbs(std::cout, m_name, " leaves room");
}

void Philosopher::eating() const
{
    Fork& leftFork{ m_table[m_seat] };
    Fork& rightFork{ m_table[m_seat + 1] };

    {
        std::scoped_lock raii_lock{ leftFork.getMutex(), rightFork.getMutex() };

        // just for testing purposes
        assert(m_table.numForks() == 0 || m_table.numForks() == 2 || m_table.numForks() == 4);

        // tracing number of used forks
        m_table.incrementNumForks();

        Logger::log(
            std::cout, m_name, " started eating (at seat ", m_seat,
            ") [", m_table.numForks(), ']', " uses forks ", m_seat, " - ", (m_seat + 1) % 5
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(Random::getNext() * AverageSleepTimeEating));

        // just for testing purposes
        m_table.decrementNumForks();
    }
}

void Philosopher::eatingDone() const
{
    Logger::log(
        std::cout, m_name, " finished eating (at seat ", m_seat,
        ") ", "   released forks ", m_seat, " - ", (m_seat + 1) % 5
    );
}

void Philosopher::thinking() const
{
    Logger::log(std::cout, m_name, " is thinking (at seat ", m_seat, ')');
    std::this_thread::sleep_for(std::chrono::milliseconds(Random::getNext() * AverageSleepTimeThinking));
}

void Philosopher::hungry() const
{
    Logger::log(std::cout, m_name, " is hungry (at seat ", m_seat, ')');
}

// ===========================================================================
// End-of-File
// ===========================================================================
