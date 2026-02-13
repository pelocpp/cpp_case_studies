// =====================================================================================
// Random.h
// =====================================================================================

#pragma once

#include <random>
#include <print>

class RandomWeights
{
private:
    std::random_device                     m_engine;
    std::mt19937                           m_generator;
    std::uniform_real_distribution<double> m_dist;

public:
    // c'tor(s)
    RandomWeights() : RandomWeights{ 123, true }
    {
    }

    RandomWeights(unsigned int seed, bool reproducible)
    {
        // if reproducible generator is preferred, use fixed seed value;
        // otherwise use std::random_device
        m_generator = std::mt19937(reproducible ? seed : m_engine());
        m_dist = std::uniform_real_distribution<double>{ 0.0, 1.0 };
    }

    // public interface
    double nextRandomNumber() {

        double nextNumber{ m_dist(m_generator) };
        return nextNumber;
    }
};

extern RandomWeights random;

// =====================================================================================
// End-of-File
// =====================================================================================
