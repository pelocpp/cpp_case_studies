// =====================================================================================
// PrimeNumberCalculator.cpp
// =====================================================================================

#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <future>
#include <atomic>
#include <latch>
#include <mutex> 

#include "PrimeNumberCalculator.h"

//void PrimeNumberCalculator::calcPrimes()
//{
//    std::vector<std::future<size_t>> tasks(ThreadCount);
//
//    auto worker = [this]() {
//
//        size_t found = calcPrimesHelper();
//
//        m_done.count_down();
//
//        return found;
//    };
//
//    for (size_t i{}; i != ThreadCount; ++i) {
//
//        std::future<size_t> future{
//            std::async(std::launch::async, worker)
//        };
//
//        tasks.push_back(std::move(future));
//    }
//
//    // block until work is done
//    m_done.wait();
//
//    // get the results
//    size_t total{};
//    for (size_t i = 0; i != ThreadCount; ++i) {
//
//        std::future<size_t> future{ std::move(tasks.back()) };
//        tasks.pop_back();
//
//        size_t partialSum{ future.get() };
//        // std::cout << "PARTIAL: " << partialSum << std::endl;
//        total += partialSum;
//    }
//
//    std::cout << "Total: " << total << std::endl;
//}

void PrimeNumberCalculator::calcPrimesEx()
{
    std::vector<std::future<void>> tasks(ThreadCount);

    auto worker = [this]() {
        calcPrimesHelperEx();
        m_done.count_down();
    };

    for (size_t i{}; i != ThreadCount; ++i) {

        std::future<void> future{
            std::async(std::launch::async, worker)
        };

        tasks.push_back(std::move(future));
    }

    // block until work is done
    m_done.wait();

    // get the results


    std::cout << "Total: " << m_count << std::endl;
}

void PrimeNumberCalculator::calcPrimesExEx()
{
    std::vector<std::future<void>> tasks(ThreadCount);

    auto worker = [this]() {
        calcPrimesHelperExEx();
        m_done.count_down();
    };

    for (size_t i{}; i != ThreadCount; ++i) {

        std::future<void> future{
            std::async(std::launch::async, worker)
        };

        tasks.push_back(std::move(future));
    }

    // block until work is done
    m_done.wait();

    // print the results
    std::cout << "Total:   " << m_primes.size() << std::endl;

    // https://www.matheretter.de/wiki/primzahlen-bis-1000
    for (int columns{}; size_t prime : m_primes) {
        std::cout << prime << " ";           // TODO: Mit WIDTH !!!!!!!!!!
        if(++columns % 16 == 0) {
            std::cout << std::endl;
        }
    };


}


// =====================================================================================

//size_t PrimeNumberCalculator::calcPrimesHelper()
//{
//    // some output
//    std::stringstream ss;
//    std::thread::id currentTID{ std::this_thread::get_id() };
//    ss << "[" << currentTID << "]: starting ..." << std::endl;
//    std::cout << ss.str();
//    ss.str("");
//
//    size_t max{ m_maximum };  // upper prime number limit
//    size_t next{ m_next++ };  // next prime number candidate
//    size_t count{};           // counter of found prime numbers in this thread
//
//    while (next < max) {
//
//        // test candidate being prime 
//        if (PrimeNumberCalculator::isPrime(next)) {
//            // increment thread specific prime number counter
//            count++;
//        }
//
//        // retrieve next prime number candidate
//        // performing atomic post-increment
//        next = m_next++;
//    }
//
//    ss << "[" << currentTID << "]: done." << std::endl;;
//    std::cout << ss.str();
//
//    return count;
//}

void PrimeNumberCalculator::calcPrimesHelperEx()
{
    // thread string with FIVE places !!!!!!!!!!!!!


    // some output
    std::stringstream ss;
    std::thread::id currentTID{ std::this_thread::get_id() };
    ss << "[" << currentTID << "]: starting ..." << std::endl;
    std::cout << ss.str();
    ss.str("");

    size_t max{ m_maximum };  // upper prime number limit
    size_t next{ m_next++ };  // next prime number candidate
   // size_t count{};           // counter of found prime numbers in this thread

    while (next < max) {

        // test if candidate being prime 
        if (PrimeNumberCalculator::isPrime(next)) {
            ++m_count;  // atomic increment
        }

        // retrieve next prime number candidate
        next = m_next++;
    }

    ss << "[" << currentTID << "]: done." << std::endl;;
    std::cout << ss.str();

  //  return count;
}

void PrimeNumberCalculator::calcPrimesHelperExEx()
{
    // some output
    std::stringstream ss;
    std::thread::id currentTID{ std::this_thread::get_id() };
    ss << "[" << currentTID << "]: starting ..." << std::endl;
    std::cout << ss.str();
    ss.str("");

    size_t max{ m_maximum };  // upper prime number limit
    size_t next{ m_next++ };  // next prime number candidate
    std::vector<size_t> primes; // thread-local prime numbers container

    while (next < max) {

        // test if candidate being prime 
        if (PrimeNumberCalculator::isPrime(next)) {
            primes.push_back(next);
        }

        // retrieve next prime number candidate
        next = m_next++;
    }

    {
        std::scoped_lock<std::mutex> lock{ m_mutex };

        std::vector<size_t> copy;
        
        std::swap(copy, m_primes);

        // no implace implementation
        std::merge(copy.begin(), copy.end(), primes.begin(), primes.end(), std::back_inserter(m_primes));
    }

    ss << "[" << currentTID << "]: done (" << primes.size() << ")." << std::endl;;
    std::cout << ss.str();
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

// =====================================================================================
// End-of-File
// =====================================================================================
