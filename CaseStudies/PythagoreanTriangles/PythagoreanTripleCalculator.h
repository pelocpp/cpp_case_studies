// ===========================================================================
// PythagoreanTripleCalculator.h
// ===========================================================================

#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>

#include "ScopedTimer.h"
#include "ParallelFor.h"
#include "PythagoreanTriple.h"

template <typename T>
class SimpleDataStore
{
private:
    size_t m_count;
    size_t m_circumference;
    std::stack<T> m_triples;

public:
    SimpleDataStore() : m_count{}, m_circumference{} {}

    size_t size() const { return m_triples.size(); }
    size_t count() const { return m_count; }
    size_t circumference() const { return m_circumference; }

    void add (size_t count, size_t circ, size_t a, size_t b, size_t c) {

        // store triple
        m_triples.emplace(a, b, c);

        // update search indices
        if (count > m_count)
        {
            m_count = count;
            m_circumference = circ;
        }
    }

    std::stack<T> data() {
        return m_triples;
    }
};

template <typename T>
class ThreadsafeDataStore
{
private:
    size_t m_count;
    size_t m_circumference;
    std::stack<T> m_triples;

    mutable std::mutex m_mutex;

public:
    ThreadsafeDataStore() : m_count{}, m_circumference{} {}

    size_t size() const { return m_triples.size(); }
    size_t count() const { return m_count; }
    size_t circumference() const { return m_circumference; }

    void add (size_t count, size_t circ, size_t a, size_t b, size_t c) {

        const std::lock_guard<std::mutex> guard(m_mutex);

        // store triple
        m_triples.emplace(a, b, c);

        // update search indices
        if (count > m_count)
        {
            m_count = count;
            m_circumference = circ;
        }
    }

    std::stack<T> data() {
        const std::lock_guard<std::mutex> guard(m_mutex);
        return m_triples;
    }
};

template <typename TStore = SimpleDataStore<PythagoreanTriple>>
class PythagoreanTripleCalculator
{
private:
    TStore m_store;

public:
    // c'tor
    PythagoreanTripleCalculator() = default;

    // getter
    size_t triplesCount() { return m_store.size(); }

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
    void calculateRange(size_t start, size_t end)
    {
        for (size_t i{ start }; i != end; ++i) {
            calculate(i);
        }
    }

    void calculate(size_t circ)
    {
        for (size_t count{}, a{ 1 }; a <= circ; ++ a) {

            for (size_t b{ a }; b <= circ; ++ b) {

                if (size_t c{ circ - a - b }; a * a + b * b == c * c) {

                    // found a pythagorean triple
                    count++;
                    m_store.add (count, circ, a, b, c);
                }
            }
        }
    }

public:
    std::string toString()
    {
        std::stringstream ss{};

        ss << "Total: " << m_store.size() << " pythagorean triples\n";
        ss << "Found: " << m_store.count() << " triangles at circumference " << m_store.circumference();



      //  ss << "TID:  " << std::this_thread::get_id() << "\t[" << start << " - " << end << "]\n";
       // std::cout << ss.str();
        return ss.str();


        //std::string s1 { std::format("Total: {} pythagorean triples\n", m_store.size()) };
        //std::string s2 { std::format("Found: {} triangles at circumference {}\n",
        //    m_store.count(), m_store.circumference()) };

        //return s1 + s2;
    }

    // helper method
    void dumpStack()
    {
        std::stack<PythagoreanTriple> stack { m_store.data()};

        if (stack.empty())
            return;

        PythagoreanTriple triple{};

        size_t lastCircumference{};

        while (! stack.empty()) {

            triple = stack.top();
            stack.pop();

            if (triple.circumference() != lastCircumference) {

                lastCircumference = triple.circumference();
                std::cout << '\n';
            }

            std::string s{ triple.toString() };
            std::cout << std::format("{:4}: {}", triple.circumference(), s) << std::endl;
        }
    }
};

// ===========================================================================
// End-of-File
// ===========================================================================
