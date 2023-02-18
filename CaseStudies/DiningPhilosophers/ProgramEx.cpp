#include <array>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <string_view>

#include "Logger.h"

namespace OriginalVersion {

    std::mutex g_lockprint;

    constexpr  int NumPhilosophers = 5;

    struct fork
    {
        std::mutex mutex;
    };

    struct table
    {
        std::atomic<bool> ready{ false };

        std::array<fork, NumPhilosophers> forks;
    };

    struct philosopher
    {
    private:
        const std::string name;
        const table& dinnertable;
        fork& left_fork;
        fork& right_fork;
        std::thread   lifethread;
        std::mt19937  rng{ std::random_device{}() };
    public:
        philosopher(std::string_view name, table const& table, fork& l, fork& r) :
            name{ name },
            dinnertable{ table },
            left_fork(l),
            right_fork(r),
            lifethread(&philosopher::dine, this)
        {
        }

        ~philosopher()
        {
            lifethread.join();
        }

        void dine()
        {
            while (!dinnertable.ready);

            do
            {
                think();
                eat();
            } while (dinnertable.ready);
        }

        void print(std::string_view text)
        {
            std::lock_guard<std::mutex> cout_lock(g_lockprint);
            std::cout
                << std::left << std::setw(10) << std::setfill(' ')
                << name << text << std::endl;
        }

        void eat()
        {
            //std::lock(left_fork.mutex, right_fork.mutex);

            //std::lock_guard<std::mutex> left_lock(left_fork.mutex, std::adopt_lock);
            //std::lock_guard<std::mutex> right_lock(right_fork.mutex, std::adopt_lock);

            std::scoped_lock lck{ left_fork.mutex, right_fork.mutex };

            print(" started eating.");

            static thread_local std::uniform_int_distribution<> dist(1, 6);
            std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng) * 50));

            print(" finished eating.");
        }

        void think()
        {
            static thread_local std::uniform_int_distribution<> wait(1, 6);
            std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 150));

            print(" is thinking ");
        }
    };

    void diningPhilosophersOriginal()
    {
        std::cout << "Dinner started!" << std::endl;

        {
            table table;

            std::array<philosopher, NumPhilosophers> philosophers
            {
               {
                  { "Aristotle", table, table.forks[0], table.forks[1] },
                  { "Platon",    table, table.forks[1], table.forks[2] },
                  { "Descartes", table, table.forks[2], table.forks[3] },
                  { "Kant",      table, table.forks[3], table.forks[4] },
                  { "Nietzsche", table, table.forks[4], table.forks[0] },
               }
            };

            table.ready = true;
            std::this_thread::sleep_for(std::chrono::seconds(20));
            table.ready = false;
        }

        std::cout << "Dinner done!" << std::endl;
    }

}

int main_original()
{
    using namespace OriginalVersion;

    diningPhilosophersOriginal();

    return 0;
}