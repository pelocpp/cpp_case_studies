// ===========================================================================
// class Table
// ===========================================================================

#include <cassert>
#include <array>
#include <future>

#include "Logger.h"

#include "DiningPhilosophers.h"
#include "Table.h"

Table::Table() 
{
    m_forks.fill(false);
    Logger::logAbs(std::cout, forksToString());
}

bool& Table::operator[] (size_t index)
{
    size_t seat{ index % 5 };
    return m_forks[seat];
}

void Table::demandForks(size_t seat)
{
    std::string forksDisplay{};

    Logger::log(std::cout, "demand forks at seat ", seat);
    {
        // RAII idiom
        std::unique_lock<std::mutex> raii{ m_mutex };

        m_condition.wait(raii, [&] {
            return (*this)[seat] == false && (*this)[seat + 1] == false;
            }
        );

        // now we own the lock, take the corresponding forks 
        (*this)[seat] = true;
        (*this)[seat + 1] = true;

        Logger::log(std::cout, "got forks at seat ", seat);

        // create current display string of forks thread-safe
        forksDisplay = forksToString();
    }

    // output latest forks display string - not necessarily to be done within critical section
    Logger::logAbs(std::cout, forksDisplay);
}

void Table::releaseForks(size_t seat)
{
    std::string forksDisplay{};

    Logger::log(std::cout, "release forks at seat ", seat);
    {
        // RAII idiom
        std::unique_lock<std::mutex> lock{ m_mutex };

        // now we own the lock, release the corresponding forks 
        (*this)[seat] = false;
        (*this)[seat + 1] = false;

        Logger::log(std::cout, "released forks at seat ", seat);

        // create current display string of forks thread-safe
        forksDisplay = forksToString();

        // wakeup other waiting  philosophers (within locked region)
        m_condition.notify_all();
    }

    // output latest forks display string - not necessarily to be done within critical section
    Logger::logAbs(std::cout, forksDisplay);
}

std::string Table::forksToString() const
{
    std::string sforks;
    for (size_t i{}; i != NumPhilosophers; i++) {
        sforks.append(m_forks[i] ? "X" : "_");
    }
    assert(sforks != "XXXXX");
    return sforks;
}

// ===========================================================================
// End-of-File
// ===========================================================================
