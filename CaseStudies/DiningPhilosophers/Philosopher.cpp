// ===========================================================================
// class Philosopher
// ===========================================================================

#include <random>
#include <array>
#include <future>

#include "Logger.h"

#include "DiningPhilosophers.h"
#include "Fork.h"
#include "PhilosopherState.h"
#include "Table.h"
#include "Philosopher.h"

Philosopher::Philosopher(Table& table, int seat)
    : m_table{ table }, m_seat{ seat }, m_activities{ 0 },
      m_state{ PhilosopherState::None }, m_running{ false } {}

void Philosopher::start()
{
    m_running = true;
    m_future = std::async(
        std::launch::async,
        [this]() {
            run();
        }
    );
}

void Philosopher::stop()
{
    m_running = false;
    m_future.get();

    Logger::logAbs(std::cout, "philosopher ", m_seat, " done: ", m_activities, " activities completed.");
}

void Philosopher::thinking()
{
    m_activities++;
    Logger::log(std::cout, "thinking at seat ", m_seat);
    m_state = PhilosopherState::Thinking;
    int milliSecondsSleeping = distribution(generator);
    std::this_thread::sleep_for(std::chrono::milliseconds(milliSecondsSleeping));
}

void Philosopher::hungry() 
{
    m_activities++;
    Logger::log(std::cout, "hungry at seat ", m_seat);
    m_state = PhilosopherState::Hungry;
    m_table.demandForks(m_seat);
}

void Philosopher::eating()
{
    m_activities++;
    Logger::log(std::cout, "eating at seat ", m_seat);
    m_state = PhilosopherState::Eating;
    int milliSecondsEating{ distribution(generator) };
    std::this_thread::sleep_for(std::chrono::milliseconds(milliSecondsEating));
}

void Philosopher::eatingDone() 
{
    m_activities++;
    Logger::log(std::cout, "eating done at seat ", m_seat);
    m_table.releaseForks(m_seat);
}

void Philosopher::run()
{
    std::thread::id philosopherThreadId{ std::this_thread::get_id() };
    Logger::logAbs(std::cout, "philosopher enters room");

    while (m_running) {
        thinking();
        hungry();
        eating();
        eatingDone();
    }

    Logger::logAbs(std::cout, "philosopher at seat ", m_seat, " quits.");
    m_state = PhilosopherState::None;
}

// initialize static class members
std::random_device Philosopher::device;
std::mt19937 Philosopher::generator(Philosopher::device());
std::uniform_int_distribution<int> Philosopher::distribution{ 
    MinSleepingMSecs, MaxSleepingMSecs
};

// ===========================================================================

void PhilosopherEx::dine()
{
    //while (!dinnertable.ready);

    //do
    //{
    //    think();
    //    eat();
    //} while (dinnertable.ready);
}

void PhilosopherEx::thinking()
{
    static thread_local std::uniform_int_distribution<> wait(1, 6);
    std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 150));

    Logger::log(std::cout, " is thinking ");
}

void PhilosopherEx::eating()
{
    //std::lock(left_fork.mutex, right_fork.mutex);

    //std::lock_guard<std::mutex> left_lock(left_fork.mutex, std::adopt_lock);
    //std::lock_guard<std::mutex> right_lock(right_fork.mutex, std::adopt_lock);

 //   std::scoped_lock lck{ left_fork.mutex, right_fork.mutex };

    // print(" started eating.");
    Logger::log(std::cout, " started eating.");

    static thread_local std::uniform_int_distribution<> dist(1, 6);
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng) * 50));

    Logger::log(std::cout, " finished eating.");
}

// ===========================================================================
// End-of-File
// ===========================================================================
