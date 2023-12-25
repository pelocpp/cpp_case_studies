// ===========================================================================
// ThreadsafeStack.h
// ===========================================================================

#pragma once

#include <exception>
#include <stack>
#include <mutex>
#include <optional>

struct empty_stack : std::exception
{
private:
    std::string m_what;

public:
    explicit empty_stack() : m_what{ std::string{ "Stack is empty!" } } {}

    explicit empty_stack(std::string msg) {
        m_what = std::move(msg);
    }

    const char* what() const noexcept override {
        return m_what.c_str();
    }
};

template<typename T>
class ThreadsafeStack
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

    ThreadsafeStack(const ThreadsafeStack&& other) noexcept
    {
        std::lock_guard<std::mutex> lock(other.m_mutex);
        m_data = std::move(other.m_data);
    }

    // public interface
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock{ m_mutex };
        m_data.push(new_value);
    }

    template<class... TArgs>
    void emplace(TArgs&&... args)
    {
        std::lock_guard<std::mutex> lock{ m_mutex };
        m_data.emplace(std::forward<TArgs>(args) ...);
    }

    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock{ m_mutex };
        if (m_data.empty()) throw empty_stack{};
        value = m_data.top();
        m_data.pop();
    }

    T tryPop()
    {
        std::lock_guard<std::mutex> lock{ m_mutex };
        if (m_data.empty()) throw std::out_of_range{ "Stack is empty!" };
        T value = m_data.top();
        m_data.pop();
        return value;
    }

    std::optional<T> tryPopOptional()
    {
        std::lock_guard<std::mutex> lock{ m_mutex };
        if (m_data.empty()) {
            return std::nullopt;
        }

        std::optional<T> result{ m_data.top() };
        m_data.pop();
        return result;
    }

    size_t size() const
    {
        std::lock_guard<std::mutex> lock{ m_mutex };
        return m_data.size();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock{ m_mutex };
        return m_data.empty();
    }
};

// ===========================================================================
// End-of-File
// ===========================================================================
