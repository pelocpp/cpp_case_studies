// ===========================================================================
// Logger.cpp
// ===========================================================================

#include <chrono>
#include <mutex>

#include "Logger.h"

std::chrono::steady_clock::time_point Logger::s_begin;
bool Logger::s_loggingEnabled{ true };
std::size_t Logger::s_nextIndex{};
std::mutex Logger::s_mutexIds;
std::map<std::thread::id, std::size_t> Logger::s_mapIds;

// ===========================================================================
// End-of-File
// ===========================================================================
