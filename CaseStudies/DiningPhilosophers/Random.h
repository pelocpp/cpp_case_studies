// ===========================================================================
// Random.h
// ===========================================================================

#pragma once

#include <random>

// #include <mutex>

class Random
{
private:
    static std::random_device m_dev;
    static inline std::mt19937 m_rng{ m_dev ()};
    static std::uniform_int_distribution<std::mt19937::result_type> m_dist6;

public:
    static std::mt19937::result_type getNext() {
        return m_dist6(m_rng);
    }
};

// ===========================================================================
// End-of-File
// ===========================================================================
