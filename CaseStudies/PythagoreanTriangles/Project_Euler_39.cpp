#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <sstream>
#include <algorithm>
#include <functional>
#include <thread>
#include <stack>
#include <thread>
#include <format>
#include <chrono>

#include "../Logger/Logger.h"
#include "../Logger/ScopedTimer.h"

#include "../20_Threadsafe_Stack/ThreadsafeStack.h"

// WEITERARBEIT:

// a) Logger intergrieren ...
// b) Hübsche Testausgaben

// c) Die Klasse / Funbktion callableWrapper separieren .. .. extra Datei

// D) Eine Fallstudie zu PythagoreanTriple schreiben ....

// ======================================================

// E) Im Repository Concurrency:

// E1) Die Klasse / Funbktion callableWrapper separieren .. .. extra Datei
// E2) Möglicherweise mit den Primzahlen wieder ein ähnliches Beispiel hinzufügen ... mit Zeitmessungen ...



// https://stackoverflow.com/questions/36246300/parallel-loops-in-c

namespace Concurrency_Parallel_For_Ex
{
    using Callable = std::function<void(size_t start, size_t end)>;

    static void callableWrapper(Callable callable, size_t start, size_t end) {

       // std::cout << "Thread " << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << std::this_thread::get_id() << std::endl;

        Logger::log(std::cout, "Thread: ", std::this_thread::get_id());

        callable(start, end);
    }

    static void parallel_for(
        size_t numElements,
        Callable callable,
        bool useThreads)
    {
        Logger::log(std::cout, ">>> parallel_for:");

        // calculate number of threads to use
        size_t numThreadsHint{ std::thread::hardware_concurrency() };
        size_t numThreads{ (numThreadsHint == 0) ? 8 : numThreadsHint };
        size_t batchSize{ numElements / numThreads };
        size_t batchRemainder{ numElements % numThreads };

        // allocate vector of uninitialized thread objects
        std::vector<std::thread> threads;

        if (useThreads) {

            // prepare multi-threaded execution
            for (size_t i{}; i != numThreads - 1; ++i) {

                size_t start{ i * batchSize };

                threads.push_back(std::move(std::thread{ callableWrapper, callable, start, start + batchSize }));
            }
        }
        else {

            // prepare single-threaded execution (for easy debugging)
            for (size_t i{}; i != numThreads - 1; ++i) {

                size_t start{ i * batchSize };
                callable(start, start + batchSize);
            }
        }

        // take care of last element - calling 'callable' synchronously 
        size_t start{ from + (numThreads - 1) * batchSize };
        callable(start, start + batchRemainder);

        // wait for the other thread to finish their task
        if (useThreads) {
           std::for_each(
               threads.begin(),
               threads.end(),
               std::mem_fn(&std::thread::join)
           );
        }

        Logger::log(std::cout, "<<< parallel_for:");
    }
}

namespace Project_Euler_39
{
    class PythagoreanTriple
    {
    private:
        std::array<size_t, 3> m_numbers;

    public:
        PythagoreanTriple() : PythagoreanTriple { 0, 0, 0} {}

        PythagoreanTriple(size_t x, size_t y, size_t z) 
            : m_numbers { x, y, z}
        {}

        size_t circumference () {
            return m_numbers[0] + m_numbers[1] + m_numbers[2];
        }

        std::string toString() {
            return std::format("[{:02},{:02},{:02}]",
                m_numbers[0], m_numbers[1], m_numbers[2]);
        }
    };

    class PythagoreanTripleCalculator
    {
    private:
        size_t m_maxNumber;
        size_t m_maxCircumference;
        size_t m_total;

        // std::stack<PythagoreanTriple> m_triples;
        Concurrency_ThreadsafeStack::ThreadsafeStack<PythagoreanTriple> m_triples;

    public:
        // c'tor
        PythagoreanTripleCalculator() 
            : m_maxNumber{}, m_maxCircumference{}, m_total{}
        {}

        // public sequential interface
        void calculateAll(size_t maxCircumference)
        {
            for (size_t circ{ 3 }; circ <= maxCircumference; ++circ) {
            
                for (size_t found{}, a{ 1 }; a <= circ; ++a) {
                
                    for (size_t b{ a }; b <= circ; ++b) {
                    
                        size_t c{ circ - a - b };

                        if (a * a + b * b == c * c) {
                        
                            // store this pythagorean triple
                            m_triples.emplace(a, b, c);
                            m_total++;

                            found++;
                            if (found > m_maxNumber)
                            {

                                m_maxNumber = found;
                                m_maxCircumference = circ;
                            }
                        }
                    }
                }
            }
        }

        void calculateAllEx(size_t maxCircumference)
        {
            for (size_t c{ 3 }; c <= maxCircumference; ++c) {

                calculateAllRectangles(c);
            }
        }

    private:
        void calculateAllRectangles(size_t circ)
        {
            for (size_t found{}, a{ 1 }; a <= circ; ++a) {
            
                for (size_t b{ a }; b <= circ; ++b) {
                
                    size_t c{ circ - a - b };

                    if (a * a + b * b == c * c) {
                    
                        // store this pythagorean triple
                        m_triples.emplace(a, b, c);  //NEED THREAD SAFE QUEUE !!!
                        m_total++;

                        found++;
                        if (found > m_maxNumber)
                        {

                            m_maxNumber = found;
                            m_maxCircumference = circ;
                        }
                    }
                }
            }
        }

    public:
        // public concurrent interface
        void process(size_t maximum, bool useThreads)
        {
            Concurrency_Parallel_For_Ex::parallel_for(
                maximum, 
                [this] (size_t start, size_t end) { 
                    processRange(start, end); 
                },
                useThreads
            );
        }

    private:
        void processRange(size_t start, size_t end)
        {
            Logger::log(std::cout, std::this_thread::get_id(), " processRange: ", start, " -> ", end);

            for (size_t i{ start }; i != end; ++i) {
                calculateAllRectangles(i);
            }
        }

    public:
        // getter
        size_t triplesCount() { return m_triples.size(); }

        std::string toString()
        {
            return std::format("Total: {} // # Identically Circumferences: {} at {}",
                m_total, m_maxNumber, m_maxCircumference);
        }

        // helper method
        void dumpStack()
        {
            if (m_triples.empty())
                return;

            Concurrency_ThreadsafeStack::ThreadsafeStack<PythagoreanTriple> copy{ m_triples };

            PythagoreanTriple triple{};

            size_t lastCircumference{};

            while (true) {

                std::optional<PythagoreanTriple> triple = copy.tryPopOptional();

                if (!triple.has_value()) {
                    break;
                }

                if (triple.value().circumference() != lastCircumference) {

                    lastCircumference = triple.value().circumference();
                    std::cout << '\n';
                }

                std::string s{ triple.value().toString() };
                std::cout << std::format("{:4}: {}", triple.value().circumference(), s) << std::endl;
            }
        }
    };
}

void test_project_euler_39_01()
{
    using namespace Project_Euler_39;

    Logger::log(std::cout, "Main:   ", std::this_thread::get_id());

    PythagoreanTripleCalculator calculator;

    {
        ScopedTimer watch{};

        // sequential interface
        // calculator.calculateAll(2000);
        // calculator.calculateAllEx(1000);
        // 
        // concurrent interface
        calculator.process(1000, true);
    }

    // calculator.dumpStack();
    Logger::log(std::cout, calculator.toString());

    Logger::log(std::cout, "Done.");
}


void test_project_euler_39()
{
    test_project_euler_39_01();
}

// ===========================================================================
// End-of-File
// ===========================================================================
