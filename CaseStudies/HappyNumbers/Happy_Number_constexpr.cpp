// =====================================================================================
// Happy_Number_constexpr.cpp
// =====================================================================================

#include <algorithm>
#include <array>
#include <cstddef>
#include <print>
#include <span>
#include <vector>

// =====================================================================================

static constexpr std::size_t sumOfSquares(std::size_t n)
{
    std::size_t squareSum{};
    while (n != 0) {
        std::size_t digit{ n % 10 };
        squareSum += digit * digit;
        n /= 10;
    }
    return squareSum;
}

// =====================================================================================

namespace Constexpr_RecursiveApproach {

    static constexpr bool isHappy(std::size_t number)
    {
        std::size_t sum{ sumOfSquares(number) };

        if (sum == 1) {
            return true;
        }
        else if (sum > 1 && sum <= 4) {
            return false;
        }
        else {
            return isHappy(sum);
        }
    }
}

// =====================================================================================

namespace Constexpr_UsingFloydsAlgorithm {

    static constexpr bool isHappy(std::size_t number)
    {
        std::size_t slow{ number };
        std::size_t fast{ number };

        do {
            slow = sumOfSquares(slow);
            fast = sumOfSquares(sumOfSquares(fast));
        }
        while (slow != fast);

        return (slow == 1) ? true : false;
    }
}

// =====================================================================================

namespace Constexpr_UsingMemoization {

    static constexpr bool isHappy(std::size_t number)
    {
        std::vector<std::size_t> checkedNumbers;

        while (true)
        {
            number = sumOfSquares(number);
            if (number == 1) {
                return true;
            }
            else if (auto pos = std::find(checkedNumbers.begin(), checkedNumbers.end(), number); pos != checkedNumbers.end()) {
                return false;
            }
            checkedNumbers.push_back(number);
        }
    }
}

// =====================================================================================

namespace HappyNumbers_Constexpr
{
    static constexpr auto countHappyNumbersLessThan(std::size_t max)
    {
        std::size_t count{};

        for (std::size_t i{ 1 }; i != max; i++) {
            if (Constexpr_RecursiveApproach::isHappy(i)) {
                ++count;
            }
        }

        return count;
    }

    static constexpr auto countHappyNumbersLessThan10{ countHappyNumbersLessThan(10) };
    static constexpr auto countHappyNumbersLessThan100{ countHappyNumbersLessThan(100) };
    static constexpr auto countHappyNumbersLessThan1000{ countHappyNumbersLessThan(1000) };

    static constexpr auto calcHappyNumbersTable ()
    {
        constexpr std::size_t TableSize = 10;

        std::array<bool, TableSize> table{};

        for (std::size_t i{ 1 }; i != TableSize; i++) {
            table[i] = Constexpr_RecursiveApproach::isHappy(i);
        }

        return table;
    }

    static constexpr auto calcHappyNumbersTableLessThan(std::size_t max)
    {
        constexpr std::size_t TableSize = 142;

        std::array<std::size_t, TableSize> table{};

        std::vector<std::size_t> numbers{};

        for (std::size_t i{ 1 }; i != max; i++) {
            if (Constexpr_RecursiveApproach::isHappy(i)) {
                numbers.push_back(i);
            }
        }

        std::size_t count = (numbers.size() < TableSize) ? numbers.size() : TableSize;

        std::copy_n(numbers.begin(), count, table.begin());

        return table;
    }

    static constexpr auto tableLessThan10{ calcHappyNumbersTableLessThan(10) };
    static constexpr auto tableLessThan100{ calcHappyNumbersTableLessThan(100) };
    static constexpr auto tableLessThan1000{ calcHappyNumbersTableLessThan(1000) };

    static void printTable(std::span<const std::size_t> table)
    {
        for (auto pos{ 0 };  auto elem : table) {
            if (elem == 0) {
                std::println();
                return;
            }
            std::print("{:5}", elem);
            ++pos;
            if (pos % 15 == 0) {
                std::println();
            }
        }
    }

    static void test_constexpr()
    {
        std::span sp{ tableLessThan1000 };
        printTable(sp);
    }
}

void main_happy_number_constexpr()
{
    HappyNumbers_Constexpr::test_constexpr();
}

// =====================================================================================
// End-of-File
// =====================================================================================
