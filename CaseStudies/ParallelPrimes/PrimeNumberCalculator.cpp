// =====================================================================================
// PrimeNumberCalculator.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <atomic>
#include <latch>

#include "PrimeNumberCalculator.h"

void PrimeNumberCalculator::calcPrimesHelper()
{
    size_t max{ m_maximum };  // upper prime number limit
    size_t next{};            // next prime number candidate
    size_t count{};           // counter of found prime numbers in this thread

    while (next < max) {

        // retrieve next prime number candidate:
        // performing atomic post-increment
        next = m_next++;

        // skip even numbers
        if (next % 2 == 0) {
            continue;
        }

        // test candidate being prime 
        if (PrimeNumberCalculator::isPrime(next)) {
            // increment thread specific prime number counter
            count++;
        }

        // retrieve next prime number candidate
        next = m_next++;
    }

    // calculation done
    m_done.count_down();
}

void PrimeNumberCalculator::calcPrimes()
{
    std::latch done{ ThreadCount };

    std::vector<std::future<void>> tasks(ThreadCount);

    auto worker = [this]() {

        calcPrimesHelper();

        // simulating still some calculation time ...
     //  std::this_thread::sleep_for(std::chrono::milliseconds(msecs));
        m_done.count_down();
    };

    //int begin{ 1 };
    //int increment{ 100 };
    //int end{ begin + increment };

    for (size_t i = 0; i != ThreadCount; ++i) {

        std::future<void> future = std::async(
            std::launch::async,
            worker
        );
        tasks.push_back(std::move(future));

        //begin = end;
        //end += increment;
    }

    // block until work is done
    done.wait();
    //Logger::log(std::cout, "All calculations done :)");

    // add partial results of worker threads
    int total{};
    for (size_t i = 0; i != ThreadCount; ++i) {
        //total += results.at(i);
        //Logger::log(std::cout, "Partial result: ", results.at(i));
    }

    // use gauss to verify : n * (n + 1) / 2 ==> 80200, if n == 4
    //Logger::log(std::cout, "Total: ", total);
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
    //size_t end{ std::sqrt(number) };
    //for (size_t i{ 3 }; i <= end; i += 2) {
    //    if (number % i == 0) {
    //        return false;
    //    }
    //}

    // found prime number
    return true;
}

// =====================================================================================
// End-of-File
// =====================================================================================
