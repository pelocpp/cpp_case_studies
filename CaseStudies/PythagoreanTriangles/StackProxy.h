// ===========================================================================
// StackProxy.h
// ===========================================================================

#pragma once

//#include <exception>
//#include <stack>
//#include <mutex>
//#include <optional>

template<typename T>
class StackProxy
{
private:
    std::stack<T>      m_data;
    mutable std::mutex m_mutex;

public:
    // c'tors
    ThreadsafeStack() {}

    // prohibit assignment operator and move assignment
    ThreadsafeStack& operator = (const ThreadsafeStack&) = delete;
    ThreadsafeStack& operator = (ThreadsafeStack&&) noexcept = delete;

    // copy and move constructor may be useful
    ThreadsafeStack(const ThreadsafeStack& other) noexcept
    {
        std::lock_guard<std::mutex> lock(other.m_mutex);
        m_data = other.m_data;
    }


};

// ===========================================================================
// End-of-File
// ===========================================================================
