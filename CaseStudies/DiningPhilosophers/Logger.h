// ===========================================================================
// Logger.h
// ===========================================================================

#pragma once

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread> 
#include <mutex>
#include <map>

class Logger {
public:
    static void enableLogging(bool enable)
    {
        s_loggingEnabled = enable;
    }

    static bool isLoggingEnabled()
    {
        return s_loggingEnabled;
    }

    template<typename ...Args>
    static void logInternal(std::ostream& os, Args&& ...args)
    {
        std::stringstream ss;
        std::thread::id currentThreadId{ std::this_thread::get_id() };
        size_t tid{ readableTID(currentThreadId) };
        std::string prefix{ "[" + std::to_string(tid) + "]: " };
        ss << prefix;

        (ss << ... << std::forward<Args>(args)) << std::endl;
        os << ss.str();
    }

    // log conditionally
    template<typename ...Args>
    static void log(std::ostream& os, Args&& ...args)
    {
        if (!s_loggingEnabled)
            return;

        logInternal(os, std::forward<Args>(args)...);
    }

    // log unconditionally
    template<typename ...Args>
    static void logAbs(std::ostream& os, Args&& ...args)
    {
        logInternal(os, std::forward<Args>(args)...);
    }

    static size_t readableTID(const std::thread::id id)
    {
        std::scoped_lock<std::mutex> raii{ s_mutexIds };
        if (s_mapIds.find(id) == s_mapIds.end()) {
            s_nextIndex++;
            s_mapIds[id] = s_nextIndex;
        }

        return s_mapIds[id];
    }

    static void startWatch() {
        s_begin = std::chrono::steady_clock::now();
    }

    static void stopWatchMilli() {
        std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
        auto duration{ std::chrono::duration_cast<std::chrono::milliseconds>(end - s_begin).count() };
        std::cout << "Elapsed time in milliseconds = " << duration << " [milliseconds]" << std::endl;
    }

    static void stopWatchMicro() {
        std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
        auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(end - s_begin).count() };
        std::cout << "Elapsed time in milliseconds = " << duration << " [microseconds]" << std::endl;
    }

private:
    static std::chrono::steady_clock::time_point s_begin;
    static bool s_loggingEnabled;
    static std::mutex s_mutexIds;
    static std::map<std::thread::id, std::size_t> s_mapIds;
    static std::size_t s_nextIndex;
};

// ===========================================================================
// End-of-File
// ===========================================================================
