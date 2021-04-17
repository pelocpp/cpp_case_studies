// =====================================================================================
// PrimeNumberCalculator.h
// =====================================================================================

#pragma once

// 78498
//constexpr size_t Minimum{ 2 };
//constexpr size_t Maximum{ 1'000'000 };
//constexpr size_t ThreadCount{ 10 };

// 25
//constexpr size_t Minimum{ 2 };
//constexpr size_t Maximum{ 100 };
//constexpr size_t ThreadCount{ 2 };

// 168
constexpr size_t Minimum{ 2 };
constexpr size_t Maximum{ 1000 };
constexpr size_t ThreadCount{ 4 };

// 
//constexpr size_t Minimum{ 1'000'000 };
//constexpr size_t Maximum{ 5'000'000 };
//constexpr size_t ThreadCount{ 2 };

class PrimeNumberCalculator
{
private:
    size_t m_minimum{ Minimum };
    size_t m_maximum{ Maximum };

    std::latch m_done{ ThreadCount };
    std::atomic<size_t> m_next{ Minimum };

    std::atomic<size_t> m_count{};
    std::vector<size_t> m_primes;
    std::mutex          m_mutex;


public:
    // c'tors
    PrimeNumberCalculator() = default;

    // getter
    size_t minimum() const;
    size_t maximum() const;
    // TODO : setter ????

    // public interface
   // void calcPrimes();
    void calcPrimesEx();
    void calcPrimesExEx();


private:
    //size_t calcPrimesHelper();
    void calcPrimesHelperEx();
    void calcPrimesHelperExEx();
    static bool isPrime(size_t number);
};

// =====================================================================================
// End-of-File
// =====================================================================================
