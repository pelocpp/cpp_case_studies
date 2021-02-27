// =====================================================================================
// ExamplesCollatzEx.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iomanip>

#include "CollatzIteratorEx.h"
#include "CollatzSequenceEx.h"

void Test01_Collatz_Ex()
{
    CollatzIteratorEx<short> iter{ 7 };
    CollatzIteratorEx<short> end{ 1 };

    while (iter != end) {
        std::cout << *iter << ' ';
        ++iter;
    }
    std::cout << std::endl;
}

void Test02_Collatz_Ex()
{
    CollatzSequenceEx<long> seq{ };
    for (int n : seq) {
        std::cout << n << ' ';
    }
    std::cout << std::endl;
}

void Test03_Collatz_Ex()
{
    CollatzSequenceEx<long> seq{ 7 };
    std::ostream_iterator<int> out{ std::cout, "  " };
    std::copy(std::begin(seq), std::end(seq), out);
    std::cout << std::endl;
}

void Test04_Collatz_Ex()
{
    CollatzSequenceEx<long> seq{ 7 };
    int sum = std::accumulate(std::begin(seq), std::end(seq), 0);
    std::cout << sum << std::endl;
}

void Test05_Collatz_Ex()
{
    std::vector<int> numbers{ };
    CollatzSequenceEx<long> seq{ 7 };
    std::copy(std::begin(seq), std::end(seq), std::back_inserter(numbers));

    for (int number : numbers) {
        std::cout << number << std::endl;
    }
}

void Test06_Collatz_Ex()
{
    CollatzSequenceEx<long> seq{ 7 };
    for (int number : seq) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

void Test07_Collatz_Ex()
{
    CollatzSequenceEx<long> seq{ 7 };

    std::string s = std::accumulate(
        std::begin(seq),
        std::end(seq),
        std::string(""), // first element
        [counter = 0](const std::string& first, const auto& next) mutable {
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

void Test08_Collatz_Ex()
{
    CollatzSequenceEx<long> seq{ 7 };

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
