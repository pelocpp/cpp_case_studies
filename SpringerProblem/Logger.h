// =====================================================================================
// Logger.h
// =====================================================================================

#pragma once

template<bool VERBOSE>
class Logger
{
public:
    template<typename ... Args>
    static inline void log(std::ostream& os, Args ... args);
};

template<>
class Logger<true>
{
public:
    template<typename ... Args>
    static inline void log(std::ostream& os, Args ... args) {
        std::stringstream ss;
        std::thread::id currentThreadId = std::this_thread::get_id();
        ss << "[" << std::setw(5) << std::right << currentThreadId << "]: ";
        (ss << ... << args) << std::endl;
        os << ss.str();
    }
};

template<>
class Logger<false>
{
public:
    template<typename ... Args>
    static inline void log(std::ostream& os, Args ... args) {}
};

// =====================================================================================
// End-of-File
// =====================================================================================
