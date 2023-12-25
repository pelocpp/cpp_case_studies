#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <thread>
#include <vector>

#include "ParallelFor.h"

constexpr bool Verbose{ true };

void callableWrapper(Callable callable, size_t start, size_t end) {

    if (Verbose) {
        std::stringstream ss{};
        ss << "TID:  " << std::this_thread::get_id() << "\t[" << start << " - " << end << "]\n";
        std::cout << ss.str();
    }

    callable(start, end);
}

void parallel_for(
    size_t from,
    size_t to,
    Callable callable,
    bool useThreads)
{
    // calculate number of threads to use
    size_t numThreadsHint{ std::thread::hardware_concurrency() };
    size_t numThreads{ (numThreadsHint == 0) ? 8 : numThreadsHint };
    size_t numElements = to - from + 1;
    size_t batchSize{ numElements / numThreads };
    size_t batchRemainder{ numElements % numThreads };

    // allocate vector of uninitialized thread objects
    std::vector<std::thread> threads;
    threads.reserve(numThreads - 1);

    if (useThreads) {

        // prepare multi-threaded execution
        for (size_t i{}; i != numThreads - 1; ++i) {

            size_t start{ from + i * batchSize };
                
            threads.push_back(
                std::move(std::thread { 
                    callableWrapper, callable, start, start + batchSize 
                })
            );
        }
    }
    else {

        // prepare single-threaded execution (for easy debugging)
        for (size_t i{}; i != numThreads - 1; ++i) {

            size_t start{ from + i * batchSize };
                
            // callable(start, start + batchSize);
            callableWrapper(callable, start, start + batchSize);
        }
    }

    // take care of last element - calling 'callable' synchronously 
    size_t start{ from + (numThreads - 1) * batchSize };
    // callable(start, to);
    callableWrapper(callable, start, to);

    // wait for the other thread to finish their task
    if (useThreads) {
        std::for_each(
            threads.begin(),
            threads.end(),
            std::mem_fn(&std::thread::join)
        );
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
