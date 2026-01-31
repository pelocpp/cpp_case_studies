// =====================================================================================
// Happy_Number.cpp
// =====================================================================================

#include <cstddef>
#include <print>
#include <unordered_set>

// =====================================================================================

// https://www.geeksforgeeks.org/dsa/happy-number/
// https://www.baeldung.com/java-happy-sad-number-test
// https://cp-algorithms.com/others/tortoise_and_hare.html
// https://www.geeksforgeeks.org/dsa/floyds-cycle-finding-algorithm/

// constexpr
// https://levelup.gitconnected.com/constexpr-all-the-things-but-gently-f567a8b93603

// viel Text
// https://dev.to/a_b_102931/the-happy-number-problem-mn2

// rekursiv
// https://medium.com/@alisabajramovic/solving-the-happy-number-algorithm-334afa34599

// Floyd's Linked List Cycle Finding Algorithm
// https://github.com/cp-algorithms
// https://cp-algorithms.com/others/tortoise_and_hare.html
// https://icelam.github.io/data-structures-and-algorithms/leetcode/202-happy-number/solution-2.html
// https://www.geeksforgeeks.org/dsa/detect-loop-in-a-linked-list/

// Wikipedia
// https://de.wikipedia.org/wiki/Fr%C3%B6hliche_Zahl

// =====================================================================================

static std::size_t sumOfSquares(std::size_t n)
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

namespace HappyNumbers_NaiveApproach  {

    // forward declaration
    static bool isHappyIntern(std::size_t number);

    static void isHappy(std::size_t number)
    {
        std::println("Start: {}", number);
        bool result{ isHappyIntern(number) };
        std::println("{} is happy: {}", number, result);
    }

    static bool isHappyIntern(std::size_t number)
    {
        const std::size_t stop{ 100 };

        std::println("Start: {}", number);
        auto n{ number };

        std::size_t count{};
        while (true)
        {
            auto prevNumber{ n };
            n = sumOfSquares(n);
            std::println("{:3} ==> {:3}", prevNumber, n);

            if (n == 1) {
                return true;
            }
            else if (count == stop) {
                std::println("Aborting calculation ...");
                return false;
            }

            ++count;
        }
    }
}

// =====================================================================================

namespace HappyNumbers_RecursiveApproach {

    // forward declaration
    static bool isHappyIntern(std::size_t number);

    static void isHappy(std::size_t number)
    {
        std::println("Start: {}", number);
        bool result{ isHappyIntern(number) };
        std::println("{} is happy: {}", number, result);
    }

    static bool isHappyIntern(std::size_t number)
    {
        std::println("  ==> {:3}", number);

        std::size_t sum{ sumOfSquares(number) };

        if (sum == 1) {
            return true;
        }
        else if (sum > 1 && sum <= 4) {
            return false;
        }
        else {
            return isHappyIntern(sum);
        }
    }
}

// =====================================================================================

namespace HappyNumbers_UsingMemoization {

    // forward declaration
    static bool isHappyIntern(std::size_t number);

    static void isHappy(std::size_t number)
    {
        std::print("Start: {:3}", number);
        bool result{ isHappyIntern(number) };
        std::println(" - is happy: {}", result);
    }

    static bool isHappyIntern(std::size_t number)
    {
        std::unordered_set<std::size_t> checkedNumbers;

        auto n{ number };
        while (true)
        {
            // auto prevNumber{ n };
            n = sumOfSquares(n);
            // std::println("{:3} ==> {:3}", prevNumber, n);

            if (n == 1) {
                return true;
            }
            else if (checkedNumbers.contains(n)) {
                return false;
            }

            checkedNumbers.insert(n);
        }
    }
}

// =====================================================================================

namespace HappyNumbers_UsingFloydsAlgorithm {

    // forward declaration
    static bool isHappyIntern(std::size_t number);

    static void isHappy(std::size_t number)
    {
        std::print("Start: {:3}", number);
        bool result{ isHappyIntern(number) };
        std::println(" - is happy: {}", result);
    }

    static bool isHappyIntern(std::size_t number)
    {
        std::size_t slow{ number };
        std::size_t fast{ number };

        do {
            // move slow number by one step
            slow = sumOfSquares(slow);

            // move fast number by two steps
            fast = sumOfSquares(sumOfSquares(fast));
        } while (slow != fast);
        
        // if both number meet at 1, then we've found a happy number
        return (slow == 1) ? true : false;
    }
}

// =====================================================================================

static void main_happy_number_10()
{
    HappyNumbers_NaiveApproach::isHappy(3);
    // HappyNumbers_NaiveApproach::isHappy(4);    // endless loop
    HappyNumbers_NaiveApproach::isHappy(19);
    // HappyNumbers_NaiveApproach::isHappy(20);   // endless loop
}

static void main_happy_number_20()
{
    HappyNumbers_RecursiveApproach::isHappy(1);
    HappyNumbers_RecursiveApproach::isHappy(2);
    HappyNumbers_RecursiveApproach::isHappy(3);
    HappyNumbers_RecursiveApproach::isHappy(4);

    HappyNumbers_RecursiveApproach::isHappy(19);
    HappyNumbers_RecursiveApproach::isHappy(20);
}

// =====================================================================================

static void main_happy_number_21()
{
    const size_t Lower = 10;
    const size_t Upper = 20;

    for (std::size_t i{ Lower }; i != Upper; ++i) {
        HappyNumbers_RecursiveApproach::isHappy(i);
    }
}

// =====================================================================================

static void main_happy_number_30()
{
    const size_t Lower = 10;
    const size_t Upper = 20;

    for (std::size_t i{ Lower }; i != Upper; ++i) {
        HappyNumbers_UsingMemoization::isHappy(i);
    }
}

// =====================================================================================

static void main_happy_number_40()
{
    const size_t Lower = 10;
    const size_t Upper = 20;

    for (std::size_t i{ Lower }; i != Upper; ++i) {
        HappyNumbers_UsingFloydsAlgorithm::isHappy(i);
    }
}

// =====================================================================================

void main_happy_number()
{
    main_happy_number_10();
    main_happy_number_20();
    main_happy_number_21();
    main_happy_number_30();
    main_happy_number_40();
}

// =====================================================================================
// End-of-File
// =====================================================================================
