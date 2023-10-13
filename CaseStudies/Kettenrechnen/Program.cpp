// =====================================================================================
// Program.cpp // Kettenrechnen
// =====================================================================================


// TO BE DONE: Nochmal mit GCC

#include <iostream>
#include <iomanip>

// #include "ChainCalculatorSTL.h"

#include "ChainCalculatorClassic.h"
#include "ChainCalculatorSTL.h"
#include "ChainCalculatorRegex.h"
#include "ChainCalculatorModern.h"

// function prototypes
void test_chain_arithmetic_00();
void test_chain_arithmetic_01();
void test_chain_arithmetic_02();
void test_chain_arithmetic_03();
void test_chain_arithmetic_04();
void test_chain_arithmetic_05();
void test_chain_arithmetic_06();
void test_chain_arithmetic_07();
void test_chain_arithmetic_10();

//void test_chain_arithmetic_00()
//{
//    using namespace ChainArithmetic_ExpressionGenerator;
//
//    auto result{ ChainArithmeticHelper::createExpression(30) };
//
//    std::cout << "Expression:" << std::endl << result << std::endl;
//}

void test_chain_arithmetic_01()
{
    using namespace ChainArithmetic_Modern;

    ChainCalculatorModern chain{};

    chain.calc(10, '+', 20, '+', 30);
    auto result{ chain.getResult() };
    std::cout << "Result: " << result << std::endl;

    chain.calc(10, '+', 20, '-', 5, '*', 3, '/', 5);
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;

    chain.calc(10, '-', 5, '*', 3, '+', 35, '/', 10);
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;
}

void test_chain_arithmetic_02()
{
    using namespace ChainArithmetic_Regex;

    ChainCalculatorRegex chain{};

    chain.calc("10 + 20 + 30");
    auto result{ chain.getResult() };
    std::cout << "Result: " << result << std::endl;

    chain.calc("10 + 20 -  5 * 3 / 5");  // 10 + 20 -  5 * 3 / 5 == 15
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;

    chain.calc("10 - 5 * 3 + 35 / 10");   //   10 - 5 * 3 + 35 / 10 == 5
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;
}

void test_chain_arithmetic_03()
{
    using namespace ChainArithmetic_Classic;

    ChainCalculatorClassic chain{};

    chain.calc("10 + 20 + 30");
    auto result{ chain.getResult() };
    std::cout << "Result: " << result << std::endl;

    chain.calc("10 + 20 -  5 * 3 / 5");  // 10 + 20 -  5 * 3 / 5 == 15
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;

    chain.calc("10 - 5 * 3 + 35 / 10");   //   10 - 5 * 3 + 35 / 10 == 5
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;
}

void test_chain_arithmetic_04()
{
    using namespace ChainArithmetic_Regex;

    ChainCalculatorRegex chain{};

    chain.calc("10 + 20 + 30");
    auto result{ chain.getResult() };
    std::cout << "Result: " << result << std::endl;

    chain.calc("10 + 20 -  5 * 3 / 5");  // 10 + 20 -  5 * 3 / 5 == 15
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;

    chain.calc("10 - 5 * 3 + 35 / 10");   //   10 - 5 * 3 + 35 / 10 == 5
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;
}

//void test_chain_arithmetic_05()
//{
//    using namespace ChainArithmetic_ExpressionGenerator;
//    using namespace ChainArithmetic_Regex;
//
//    auto expression{ ChainArithmeticHelper::createExpression(5) };
//    std::cout << "Expression: " << expression << std::endl;
//
//    ChainCalculator chain{};
//    chain.calc(expression);
//    auto result{ chain.getResult() };
//    std::cout << "Result: " << result << std::endl;
//}

void test_chain_arithmetic_06()
{
    ChainArithmetic_Regex::ChainCalculatorRegex chain{};
    std::string expression{ "2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 - 1" };
    chain.calc(expression);
    auto result{ chain.getResult() };
    std::cout << "Result: " << result << std::endl;

    ChainArithmetic_Modern::ChainCalculatorModern chainModern{};
    chainModern.calc(2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '-', 1);
    result = chainModern.getResult();
    std::cout << "Result: " << result << std::endl;
}

void printResults(
    std::string tag,
    std::chrono::high_resolution_clock::time_point startTime,
    std::chrono::high_resolution_clock::time_point endTime)
{
    std::cout
        << tag
        << std::fixed
        << std::setprecision(9)
        << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime).count()
        << " msecs."
        << std::endl;
}

void test_chain_arithmetic_10()
{
    constexpr int MaxIteration = 1'000;

    {
        ChainArithmetic_Classic::ChainCalculatorClassic chain{};
        std::string expression{ "2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 - 1" };

        const auto startTime{ std::chrono::high_resolution_clock::now() };
        for (size_t i{}; i != MaxIteration; ++i) {
            chain.calc(expression);
        }
        const auto endTime{ std::chrono::high_resolution_clock::now() };

        printResults("Classic: ", startTime, endTime);
    }

    {
        ChainArithmetic_Regex::ChainCalculatorRegex chain{};
        std::string expression{ "2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 - 1" };

        const auto startTime{ std::chrono::high_resolution_clock::now() };
        for (size_t i{}; i != MaxIteration; ++i) {
            chain.calc(expression);
        }
        const auto endTime{ std::chrono::high_resolution_clock::now() };

        printResults("Regex:   ", startTime, endTime);
    }

    {
        ChainArithmetic_STL::ChainCalculatorSTL chain{};

        const auto startTime{ std::chrono::high_resolution_clock::now() };
        for (size_t i{}; i != MaxIteration; ++i) {
            chain.calc(2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '-', 1);
        }
        const auto endTime{ std::chrono::high_resolution_clock::now() };

        printResults("STL:     ", startTime, endTime);
    }

    {
        ChainArithmetic_Modern::ChainCalculatorModern chain{};

        const auto startTime{ std::chrono::high_resolution_clock::now() };
        for (size_t i{}; i != MaxIteration; ++i) {
            chain.calc(2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '-', 1);
        }
        const auto endTime{ std::chrono::high_resolution_clock::now() };

        printResults("Modern:  ", startTime, endTime);
    }
}

void test_chain_arithmetic_07()
{
    ChainArithmetic_STL::ChainCalculatorSTL chain{};
    chain.calc(10, '+', 20, '+', 30);
    auto result{ chain.getResult() };
    std::cout << "Result: " << result << std::endl;

    chain.calc(10, '+', 20, '-', 5, '*', 3, '/', 5);
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;

    chain.calc(10, '-', 5, '*', 3, '+', 35, '/', 10);
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;
}

int main()
{
    test_chain_arithmetic_00();
    test_chain_arithmetic_01();
    test_chain_arithmetic_02();
    test_chain_arithmetic_03();
    test_chain_arithmetic_04();
    test_chain_arithmetic_05();
    test_chain_arithmetic_06();
    test_chain_arithmetic_07();
    test_chain_arithmetic_10();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
