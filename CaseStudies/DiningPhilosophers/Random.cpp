// ===========================================================================
// Random.cpp
// ===========================================================================

#include <iostream>

#include "Random.h"

std::random_device Random::m_dev{};

std::uniform_int_distribution<std::mt19937::result_type> Random::m_dist6{1, 6};

std::mt19937::result_type Random::getNext() {
    return Random::m_dist6(m_rng);
}

void testRandom()
{
    for (size_t i{}; i != 20; ++i) {
        std::cout << Random::getNext() << std::endl;
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
