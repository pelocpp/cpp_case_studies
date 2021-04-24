// =====================================================================================
// PrimeNumberCalculator.cpp
// =====================================================================================

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <thread>
#include <future>
#include <atomic>
#include <latch>
#include <mutex> 

#include "PrimeNumberCalculator.h"

void PrimeNumberCalculator::calcPrimes()
{
    std::latch done{ m_threadCount };
    std::vector<std::future<void>> tasks(m_threadCount);
    m_next = m_minimum;
    m_count = 0;

    auto worker = [&]() {
        calcPrimesHelper();
        done.count_down();
    };

    for (size_t i{}; i != m_threadCount; ++i) {

        std::future<void> future{
            std::async(std::launch::async, worker)
        };

        tasks.push_back(std::move(future));
    }

    done.wait();
    printResult(m_count);
}

void PrimeNumberCalculator::calcPrimesUsingThread()
{
    std::latch done{ m_threadCount };
    m_next = m_minimum;
    m_count = 0;

    for (size_t i{}; i != m_threadCount; ++i) {

        std::thread t{
            [&]() {
                calcPrimesHelper();
                done.count_down();
            }
        };
        t.detach();
    }

    done.wait();
    printResult(m_count);
}

void PrimeNumberCalculator::calcPrimesEx()
{
    std::latch done{ m_threadCount };
    std::vector<std::future<void>> tasks(m_threadCount);
    m_next = m_minimum;
    m_count = 0;
    m_primes.clear();

    auto worker = [&]() {
        calcPrimesHelperEx();
        done.count_down();
    };

    for (size_t i{}; i != m_threadCount; ++i) {

        std::future<void> future{
            std::async(std::launch::async, worker)
        };

        tasks.push_back(std::move(future));
    }

    done.wait();
    printResult(m_primes.size());
}

// =====================================================================================
// helpers

void PrimeNumberCalculator::calcPrimesHelper()
{
    printHeader();

    size_t max{ m_maximum };  // upper prime number limit
    size_t next{ m_next++ };  // next prime number candidate
    size_t count{};           // thread-local counter - just for statistics

    while (next < max) {

        // test if candidate being prime 
        if (isPrime(next)) {
            ++m_count;  // atomic increment
            ++count;
        }

        // retrieve next prime number candidate
        next = m_next++;
    }

    printFooter(count);
}

void PrimeNumberCalculator::calcPrimesHelperEx()
{
    printHeader();

    size_t max{ m_maximum };  // upper prime number limit
    size_t next{ m_next++ };  // next prime number candidate
    std::vector<size_t> primes;  // thread-local prime numbers container

    while (next < max) {

        // test if candidate being prime 
        if (isPrime(next)) {
            primes.push_back(next);
        }

        // retrieve next prime number candidate
        next = m_next++;
    }

    if (primes.size() != 0) 
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };

        std::vector<size_t> copy;

        std::swap(copy, m_primes);

        // no inplace algorithm
        std::merge(
            copy.begin(), 
            copy.end(),
            primes.begin(), 
            primes.end(), 
            std::back_inserter(m_primes)
        );
    }

    printFooter(primes.size());
}

bool PrimeNumberCalculator::isPrime(size_t number)
{
    // the smallest prime number is 2
    if (number <= 2) {
        return number == 2;
    }

    // even numbers other than 2 are not prime
    if (number % 2 == 0) {
        return false;
    }

    // check odd divisors from 3 to the square root of the number
    size_t end{ static_cast<size_t>(ceil(std::sqrt(number))) };
    for (size_t i{ 3 }; i <= end; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }

    // found prime number
    return true;
}

void PrimeNumberCalculator::printResult(size_t count)
{
    std::cout 
        << "From " << m_minimum << " to " << m_maximum << ": found " 
        << count << " prime numbers." << std::endl;

    if (!m_primes.empty()) {
        for (int columns{}; size_t prime : m_primes) {
            std::cout << std::setw(5) << std::right << prime << " ";
            if (++columns % 16 == 0) {
                std::cout << std::endl;
            }
        };
    }
    std::cout << std::endl;
}

void PrimeNumberCalculator::printHeader()
{
    std::stringstream ss;
    std::thread::id currentTID{ std::this_thread::get_id() };
    ss << "[" << std::setw(5) << std::right << currentTID << "]: starting ..." << std::endl;
    std::cout << ss.str();
    ss.str("");
}

void PrimeNumberCalculator::printFooter(size_t count)
{
    std::stringstream ss;
    std::thread::id currentTID{ std::this_thread::get_id() };
    ss << "[" << std::setw(5) << std::right << currentTID << "]: found " << count << '.' << std::endl;
    std::cout << ss.str();
}

// =====================================================================================
// End-of-File
// =====================================================================================
