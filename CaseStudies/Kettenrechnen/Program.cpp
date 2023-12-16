// =====================================================================================
// Program.cpp // Kettenrechnen
// =====================================================================================

// TO BE DONE: Mit gcc nochmal überprüfen !!!

#include <iostream>
#include <iomanip>
#include <chrono>

#include "ChainExpressionGenerator.h"

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
void test_chain_arithmetic_10();

void test_chain_arithmetic_00()
{
    Token<int> tok{};
    std::cout << "Token: " << tok << std::endl;

    Token<OperandType> tok10{ OperatorType::AddOp };
    Token<OperandType> tok11{ OperatorType::SubOp };
    Token<OperandType> tok12{ OperatorType::MulOp };
    Token<OperandType> tok13{ OperatorType::DivOp };

    std::cout << "Token 10: " << tok10 << std::endl;
    std::cout << "Token 11: " << tok11 << std::endl;
    std::cout << "Token 12: " << tok12 << std::endl;
    std::cout << "Token 13: " << tok13 << std::endl;

    Token<size_t> tok20{ 0 };
    Token<size_t> tok21{ 1 };
    Token<size_t> tok22{ 1'000 };
    Token<size_t> tok23{ 1'000'000 };

    std::cout << "Token 20: " << tok20 << std::endl;
    std::cout << "Token 21: " << tok21 << std::endl;
    std::cout << "Token 22: " << tok22 << std::endl;
    std::cout << "Token 23: " << tok23 << std::endl;
}

void test_chain_arithmetic_01()
{
    using namespace ChainArithmetic_ExpressionGenerator;

    auto result{ ChainExpressionGenerator::createExpression(30) };

    std::cout << "Expression:" << std::endl << result << std::endl;
}

void test_chain_arithmetic_02()
{
    using namespace ChainArithmetic_Classic;

    ChainCalculatorClassic chain{};

    chain.calc("10 + 20 + 30");
    auto result{ chain.getResult() };
    std::cout << "Result: " << result << std::endl;

    chain.calc("1 + 3 * 5 - 2 * 2 - 8 / 2");
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;

    chain.calc("10 + 20 -  5 * 3 / 5");  // 10 + 20 - 5 * 3 / 5 == 15
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;

    chain.calc("10 - 5 * 3 + 35 / 10");   //   10 - 5 * 3 + 35 / 10 == 5
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;
}

void test_chain_arithmetic_03()
{
    using namespace ChainArithmetic_STL;

    ChainCalculatorSTL chain{};

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

void test_chain_arithmetic_04()
{
    using namespace ChainArithmetic_Regex;

    ChainCalculatorRegex chain{};

    chain.calc("10 + 20 + 30");
    auto result{ chain.getResult() };
    std::cout << "Result: " << result << std::endl;

    chain.calc("10 + 20 -  5 * 3 / 5");
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;

    chain.calc("10 - 5 * 3 + 35 / 10");
    result = chain.getResult();
    std::cout << "Result: " << result << std::endl;
}

void test_chain_arithmetic_05()
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

void test_chain_arithmetic_06()
{
    using namespace ChainArithmetic_ExpressionGenerator;
    using namespace ChainArithmetic_Regex;

    auto expression{ ChainExpressionGenerator::createExpression(5) };
    std::cout << "Expression: " << expression << std::endl;

    ChainCalculatorRegex chain{};
    chain.calc(expression);
    auto result{ chain.getResult() };
    std::cout << "Result: " << result << std::endl;
}

void test_chain_arithmetic_07()
{
    //ChainArithmetic_Regex::ChainCalculatorRegex chain{};
    //std::string expression{ "2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 - 1" };
    //chain.calc(expression);
    //auto result{ chain.getResult() };
    //std::cout << "Result: " << result << std::endl;

    ChainArithmetic_Modern::ChainCalculatorModern chainModern{};
    chainModern.calc(2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '-', 1);
    auto result = chainModern.getResult();
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
    constexpr int MaxIteration = 100'000;

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
        ChainArithmetic_STL::ChainCalculatorSTL chain{};

        const auto startTime{ std::chrono::high_resolution_clock::now() };
        for (size_t i{}; i != MaxIteration; ++i) {
            chain.calc(2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '-', 1);
        }
        const auto endTime{ std::chrono::high_resolution_clock::now() };

        printResults("STL:     ", startTime, endTime);
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
        ChainArithmetic_Modern::ChainCalculatorModern chain{};

        const auto startTime{ std::chrono::high_resolution_clock::now() };
        for (size_t i{}; i != MaxIteration; ++i) {
            chain.calc(2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '*', 2, '-', 1);
        }
        const auto endTime{ std::chrono::high_resolution_clock::now() };

        printResults("Modern:  ", startTime, endTime);
    }
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
