// =====================================================================================
// PrimeNumberCalculator.h
// =====================================================================================

#pragma once

/*
 * Results:
 * 1 .. 100:        25 prime numbers
 * 1 .. 1'000:      168 prime numbers
 * 1 .. 1'000'000:  78498 prime numbers
 */

constexpr size_t Minimum{ 2 };
constexpr size_t Maximum{ 100 };             //  1'000,  1'000'000
constexpr std::ptrdiff_t ThreadCount{ 2 };   //  3, 4, 12

class PrimeNumberCalculator
{
private:
    size_t m_minimum{ Minimum };
    size_t m_maximum{ Maximum };
    std::ptrdiff_t m_threadCount { ThreadCount };

    std::atomic<size_t> m_next{ Minimum };
    std::atomic<size_t> m_count{};

    std::vector<size_t> m_primes;
    std::mutex          m_mutex;

public:
    // c'tors
    PrimeNumberCalculator() = default;

    // getter / setter
    size_t minimum() const { return m_minimum; }
    size_t maximum() const { return m_maximum; }
    size_t threadCount() const { return m_threadCount; }
    void minimum(size_t minimum) { m_minimum = minimum; }
    void maximum(size_t maximum) { m_maximum = maximum; }
    void threadCount(size_t threadCount) { m_threadCount = threadCount; }

    // public interface
    void calcPrimes();
    void calcPrimesUsingThread();
    void calcPrimesEx();

private:
    void calcPrimesHelper();
    void calcPrimesHelperEx();
    void printResult(size_t);

    static bool isPrime(size_t number);
    static void printHeader();
    static void printFooter(size_t);
};

// =====================================================================================
// End-of-File
// =====================================================================================
