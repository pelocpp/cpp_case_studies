// ===========================================================================
// Simulation.cpp
// ===========================================================================

//#include <array>
//#include <mutex>
//#include <future>
//#include <atomic>
//#include <chrono>
//#include <iostream>
//#include <string>
//#include <random>
//#include <string_view>
//

#include "DiningPhilosophers.h"
#include "Logger.h"
#include "Table.h"
#include "Philosopher.h"
#include "Simulation.h"

//#include "Random.h"

void Simulation::simulation()
{
    std::thread::id mainThreadId{ std::this_thread::get_id() };
    size_t mainTid{ Logger::readableTID(mainThreadId) };

    Logger::log(std::cout,
        "Dining Philosophers Simulation [TID=",
        std::to_string(Logger::readableTID(mainThreadId)),
        "]"
    );

    Logger::enableLogging(true);

    Table table{};

    std::array<Philosopher, NumPhilosophers> philosophers
    {
        {
            { "Philosopher 1", table, 0},
            { "Philosopher 2", table, 1},
            { "Philosopher 3", table, 2},
            { "Philosopher 4", table, 3},
            { "Philosopher 5", table, 4}
        }
    };

    // start simulation
    for (Philosopher& p : philosophers) {
        p.start();
    }

    // set duration time of this simulation
    std::this_thread::sleep_for(std::chrono::milliseconds(SimulationDuration));

    // terminate simulation
    for (Philosopher& p : philosophers) {
        p.stop();
    }

    Logger::logAbs(std::cout, "Simulation Done.");
}

// ===========================================================================
// End-of-File
// ===========================================================================
