#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <functional>
#include <thread>
//#include <stack>
#include <format>

#include "ScopedTimer.h"

#include "ThreadsafeStack.h"
#include "ParallelFor.h"

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
    ThreadsafeStack<PythagoreanTriple> m_triples;

public:
    // c'tor
    PythagoreanTripleCalculator() 
        : m_maxNumber{}, m_maxCircumference{}, m_total{}
    {}

    // public sequential interface
    void calculateSeq(size_t max)
    {
        for (size_t circ{ 3 }; circ < max; ++circ) {

            calculate(circ);
        }
    }

    // public concurrent interface
    void calculatePar(size_t maximum, bool useThreads)
    {
        parallel_for(
            3,
            maximum,
            [this](size_t start, size_t end) {
                calculateRange(start, end);
            },
            useThreads
        );
    }

private:
    void calculate(size_t circ)
    {
        for (size_t found{}, a{ 1 }; a <= circ; ++a) {
            
            for (size_t b{ a }; b <= circ; ++b) {
                
                // size_t c{ circ - a - b };

                if (size_t c{ circ - a - b }; a * a + b * b == c * c) {
                    
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

private:
    void calculateRange(size_t start, size_t end)
    {
        for (size_t i{ start }; i != end; ++i) {
            calculate(i);
        }
    }

public:
    // getter
    size_t triplesCount() { return m_triples.size(); }

    std::string toString()
    {
        std::string s1 { std::format("Total: {} pythagorean triples\n", m_total) };
        std::string s2 { std::format("Found: {} triangles at circumference {}\n",
            m_maxNumber, m_maxCircumference) };

        return s1 + s2;
    }

    // helper method
    void dumpStack()
    {
        if (m_triples.empty())
            return;

        ThreadsafeStack<PythagoreanTriple> copy{ m_triples };

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

void test_pythagorean_triples_01 ()
{
   // using namespace Project_Euler_39;

   // Logger::log(std::cout, "Main:   ", std::this_thread::get_id());


    std::cout << "Main: " << std::this_thread::get_id() << std::endl;

    PythagoreanTripleCalculator calculator;

    {
        ScopedTimer watch{};

        // calculator.calculateSeq(1000);
        calculator.calculatePar(1000, false);
    }

    std::cout << calculator.toString();
    std::cout << "Done." << std::endl;
}


// ===========================================================================
// End-of-File
// ===========================================================================
