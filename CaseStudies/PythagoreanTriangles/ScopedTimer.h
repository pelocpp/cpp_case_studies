// ===========================================================================
// ScopedTimer.h
// ===========================================================================

#pragma once

#include <iostream>
#include <chrono>

class ScopedTimer
{
private:
    std::chrono::steady_clock::time_point m_begin;

public:
    ScopedTimer() {
        m_begin = std::chrono::steady_clock::now();
    }

    ~ScopedTimer() {
        std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
        auto duration{ std::chrono::duration_cast<std::chrono::milliseconds>(end - m_begin).count() };
        std::cout << "Elapsed time: " << duration << " [milliseconds]" << std::endl;
    }

    // no copying or moving
    ScopedTimer(const ScopedTimer&) = delete;
    auto operator=(const ScopedTimer&)->ScopedTimer & = delete;

    ScopedTimer(ScopedTimer&&) = delete;
    auto operator=(ScopedTimer&&)->ScopedTimer & = delete;
};

// ===========================================================================
// End-of-File
// ===========================================================================
