// ===========================================================================
// Dining Philosophers Program
// ===========================================================================

#include <random>
#include <array>
#include <future>

#include "Logger.h"

#include "DiningPhilosophers.h"
#include "PhilosopherState.h"
#include "Table.h"
#include "Philosopher.h"

void testDiningPhilosophers()
{
    Logger::enableLogging(true);

    std::thread::id mainThreadId = std::this_thread::get_id();
    size_t mainTid = Logger::readableTID(mainThreadId);
    Logger::log(std::cout,
        "Dining Philosophers Simulation [TID=",
        std::to_string(Logger::readableTID(mainThreadId)),
        "]"
    );

    Logger::enableLogging(false);

    Table table;

    Philosopher p1(table, 0);
    Philosopher p2(table, 1);
    Philosopher p3(table, 2);
    Philosopher p4(table, 3);
    Philosopher p5(table, 4);

    p1.start();
    p2.start();
    p3.start();
    p4.start();
    p5.start();

    // set duration time of this simulation
    std::this_thread::sleep_for(std::chrono::milliseconds(SimulationDuration));

    // terminate simulation
    p1.stop();
    p2.stop();
    p3.stop();
    p4.stop();
    p5.stop();

    Logger::logAbs(std::cout, "Done.");
}

//int main()
//{
//    testDiningPhilosophers();
//    return 0;
//}

// ===========================================================================
// End-of-File
// ===========================================================================
