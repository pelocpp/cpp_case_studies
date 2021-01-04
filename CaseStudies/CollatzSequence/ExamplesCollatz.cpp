// =====================================================================================
// ExamplesCollatz.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iomanip>

#include "CollatzIterator.h"
#include "CollatzSequence.h"

// Default Sequence testen ,,,, mit dem 1 er 

void Test01_Collatz()
{
    CollatzIterator iter{ 7 };
    CollatzIterator end{ 1 };

    while (iter != end) {
        std::cout << *iter << ' ';
        ++iter;
    }
}

void Test02_Collatz()
{
    CollatzSequence seq{ 17 };
    for (int n : seq) {
        std::cout << n << ' ';
    }
}

void Test03_Collatz()
{
    CollatzSequence seq{ 17 };
    std::ostream_iterator<int> out{ std::cout, "  " };
    std::copy(std::begin(seq), std::end(seq), out);
}

void Test04_Collatz()
{
    CollatzSequence seq{ 17 };
    int sum = std::accumulate(std::begin(seq), std::end(seq), 0);
    std::cout << sum << std::endl;
}

void Test05_Collatz()
{
    std::vector<int> numbers{};
    CollatzSequence seq{ 7 };
    std::copy(std::begin(seq), std::end(seq), std::back_inserter(numbers));

    for (int number : numbers) {
        std::cout << number << std::endl;
    }
}

void Test06_Collatz()
{
    CollatzSequence seq{ 7 };
    for (int number : seq) {
        std::cout << number << " ";
    }
}

void Test07_Collatz()
{
    CollatzSequence seq{ 7 };

    std::string s = std::accumulate(
        std::begin(seq),
        std::end(seq),
        std::string(""), // first element
        [counter = 0] (const std::string& first, const auto& next) mutable {
            counter++;
            std::ostringstream ss;
            ss << "[" << std::setfill('0') << std::setw(2) << counter << "]"
                << ": " << std::setfill(' ') << std::setw(5)
                << std::right << next << std::endl;

            return first + ss.str();
        }
    );

    std::cout << s << std::endl;
}

void Test08_Collatz()
{
    CollatzSequence seq{ 17 };

    //std::iterator_traits<CollatzIterator>::difference_type count 
    //    = std::distance(std::begin(seq), std::end(seq));

    // or - same as

    //CollatzIterator::difference_type count
    //    = std::distance(std::begin(seq), std::end(seq));

    // or - same as

    int count = std::distance(std::begin(seq), std::end(seq));

    std::cout << count << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
