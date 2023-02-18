// ===========================================================================
// Random.cpp
// ===========================================================================

// #include <mutex>

#include <random>

#include "Random.h"

std::random_device Random::m_dev{};

//std::uniform_int_distribution<std::mt19937::result_type> Random::m_dist6 = [] {
//    return std::uniform_int_distribution<std::mt19937::result_type> {1, 6};
//}();

std::uniform_int_distribution<std::mt19937::result_type> Random::m_dist6{1, 6};

// ===========================================================================
// End-of-File
// ===========================================================================
