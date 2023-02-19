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
//#include "Logger.h"
//#include "Random.h"
//#include "DiningPhilosophers.h"

//namespace OriginalVersionModified {
//
//    class Fork
//    {
//    private:
//        std::mutex m_mutex;
//
//    public:
//        std::mutex& getMutex() { return m_mutex; }
//    };
//
//    class Table
//    {
//    private:
//        std::array<Fork, NumPhilosophers> m_forks;
//        std::atomic<int> m_numForksInUse;
//
//    public:
//        Table() : m_numForksInUse{} {}
//
//        Fork& operator[] (size_t index)
//        {
//            size_t seat{ index % 5 };
//            return m_forks[seat];
//        }
//
//        void incrementNumForks() {
//            m_numForksInUse.fetch_add(2);
//        }
//
//        void decrementNumForks() {
//            m_numForksInUse.fetch_sub(2);
//        }
//
//        int numForks() const {
//            return m_numForksInUse.load();
//        }
//    };
//
//    class Philosopher
//    {
//    private:
//        std::string m_name;
//        Table&      m_table;
//        size_t      m_seat;   // 0 .. 4
//
//        // threading utils
//        std::future<void> m_future;
//        bool              m_running;
//
//    public:
//        Philosopher(std::string_view name, Table& table, size_t seat) :
//            m_name{ name },
//            m_table{ table },
//            m_seat{ seat },
//            m_running{ false }
//        {}
//
//        void start()
//        {
//            m_running = true;
//            m_future = std::async(
//                std::launch::async, [this]() { dine(); }
//            );
//        }
//
//        void stop()
//        {
//            m_running = false;
//            m_future.get();
//        }
//
//        void dine() const
//        {
//            std::thread::id philosopherThreadId{ std::this_thread::get_id() };
//            Logger::logAbs(std::cout, m_name, " enters room [", philosopherThreadId, ']');
//
//            while (m_running) {
//                thinking();
//                hungry();
//                eating();
//                eatingDone();
//            }
//
//            Logger::logAbs(std::cout, m_name, " leaves room");
//        }
//
//        void eating() const
//        {
//            Fork& leftFork{ m_table[m_seat] };
//            Fork& rightFork{ m_table[m_seat+1] };
//
//            {
//                std::scoped_lock raii_lock{ leftFork.getMutex(), rightFork.getMutex() };
//
//                // just for testing purposes
//                m_table.incrementNumForks();
//
//                Logger::log(
//                    std::cout, m_name, " started eating (at seat ", m_seat,
//                    ") [", m_table.numForks(), ']', " uses forks ", m_seat, " - ", (m_seat + 1) % 5
//                );
//
//                std::this_thread::sleep_for(std::chrono::milliseconds(Random::getNext() * 300));
//
//                // just for testing purposes
//                m_table.decrementNumForks();
//            }
//        }
//
//        void eatingDone() const
//        {
//            Logger::log(
//                std::cout, m_name, " finished eating (at seat ", m_seat,
//                ") ", "   released forks ", m_seat, " - ", (m_seat + 1) % 5
//            );
//        }
//
//        void thinking() const
//        {
//            Logger::log(std::cout, m_name, " is thinking (at seat ", m_seat, ')');
//            std::this_thread::sleep_for(std::chrono::milliseconds(Random::getNext() * 100));
//        }
//
//        void hungry() const
//        {
//            Logger::log(std::cout, m_name, " is hungry (at seat ", m_seat, ')');
//        }
//    };
//
//    class DiningPhilosophersSimulation
//    {
//    public:
//        static void simulation()
//        {
//            std::thread::id mainThreadId{ std::this_thread::get_id() };
//            size_t mainTid{ Logger::readableTID(mainThreadId) };
//            
//            Logger::log(std::cout,
//                "Dining Philosophers Simulation [TID=",
//                std::to_string(Logger::readableTID(mainThreadId)),
//                "]"
//            );
//
//            Logger::enableLogging(true);
//
//            Table table{};
//
//            std::array<Philosopher, NumPhilosophers> philosophers
//            {
//               {
//                  { "Philosopher 1", table, 0},
//                  { "Philosopher 2", table, 1},
//                  { "Philosopher 3", table, 2},
//                  { "Philosopher 4", table, 3},
//                  { "Philosopher 5", table, 4}
//               }
//            };
//
//            // start simulation
//            for (Philosopher& p : philosophers) {
//                p.start();
//            }
//
//            // set duration time of this simulation
//            std::this_thread::sleep_for(std::chrono::milliseconds(SimulationDuration));
//
//            // terminate simulation
//            for (Philosopher& p : philosophers) {
//                p.stop();
//            }
//
//            Logger::logAbs(std::cout, "Simulation Done.");
//        }
//    };
//}


#include "Simulation.h"

int main()
{
   // using namespace OriginalVersionModified;

    Simulation::simulation();
    //testRandom();

    return 0;
}