// =====================================================================================
// PrimeNumberCalculator.h
// =====================================================================================

#pragma once

constexpr size_t Minimum{ 2 };
constexpr size_t Maximum{ 100 };
constexpr std::ptrdiff_t ThreadCount{ 2 };
// 25 primes

//constexpr size_t Minimum{ 2 };
//constexpr size_t Maximum{ 1000 };
// 168 primes
//
//constexpr size_t Minimum{ 2 };
//constexpr size_t Maximum{ 1'000'000 };
// 78498 primes

class PrimeNumberCalculator
{
private:
    size_t m_minimum{ Minimum };
    size_t m_maximum{ Maximum };
    std::ptrdiff_t m_threadCount { ThreadCount };

  //  std::latch m_done{ ThreadCount };
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
    std::ptrdiff_t threadCount() const { return m_threadCount; }
    void minimum(size_t minimum) { m_minimum = minimum; }
    void maximum(size_t maximum) { m_maximum = maximum; }
    void threadCount(size_t threadCount) { m_threadCount = threadCount; }

    // public interface
    void calcPrimes();
    void calcPrimesEx();

private:
    void calcPrimesHelper();
    void calcPrimesHelperEx();
    void printResult();

    static bool isPrime(size_t number);
    static void printHeader();
    static void printFooter(size_t);
};

// =====================================================================================
// End-of-File
// =====================================================================================
