// =====================================================================================
// Log.h
// =====================================================================================

#pragma once

template<typename ...Args>
inline void log(bool verbose, std::ostream& os, Args ...args)
{
    if (verbose) {
        std::stringstream ss;
        std::thread::id currentThreadId = std::this_thread::get_id();
        ss << "[" << std::setw(5) << std::right << currentThreadId << "]: ";
        (ss << ... << args) << std::endl;
        os << ss.str();
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
