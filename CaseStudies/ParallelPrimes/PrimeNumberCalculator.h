// =====================================================================================
// PrimeNumberCalculator.h
// =====================================================================================

#pragma once

constexpr size_t ThreadCount{ 4 };

class PrimeNumberCalculator
{
private:
    size_t m_minimum{ 2 };
    size_t m_maximum{ 100 };

    std::latch m_done{ ThreadCount };
    std::atomic<size_t> m_next;

public:
    // c'tors
    PrimeNumberCalculator() = default;

    // getter
    size_t minimum() const;
    size_t maximum() const;
    // TODO : setter ????

    // public interface
    void calcPrimes();
    void calcPrimesHelper();
    static bool isPrime(size_t number);
};

// =====================================================================================
// End-of-File
// =====================================================================================
