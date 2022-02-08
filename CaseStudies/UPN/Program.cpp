// =====================================================================================
// Program.cpp / Umgekehrte Polnische Notation (UPN)
// =====================================================================================

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <type_traits>
#include <regex>
#include <cmath>

#include "Token.h"
#include "Scanner.h"
#include "PostfixCalculator.h"
#include "InfixToPostfixConverter.h"

// testing tokens
void test_01_01()
{
    Token<size_t> tok1{ TokenType::LBracket };
    Token<size_t> tok2{ TokenType::RBracket };
    Token<size_t> tok3{ OperatorType::AddOp };
    Token<size_t> tok4{ 12345 };

    std::cout << tok1 << std::endl;
    std::cout << tok2 << std::endl;
    std::cout << tok3 << std::endl;
    std::cout << tok4 << std::endl;
}

void test_01_02()
{
    Token<int> tok1{ TokenType::LBracket };
    Token<int> tok2{ TokenType::RBracket };
    Token<int> tok3{ OperatorType::AddOp };
    Token<int> tok4{ 12345 };

    std::cout << tok1 << std::endl;
    std::cout << tok2 << std::endl;
    std::cout << tok3 << std::endl;
    std::cout << tok4 << std::endl;
}

// testing scanner
void test_02_01()
{
    Scanner<size_t> scanner;
    scanner.set("1 2 *");
    std::cout << scanner.get() << std::endl;
}

void test_02_02()
{
    Scanner<int> scanner;
    scanner.set("1 2 - 3 -");
    scanner.scan();
    for (const auto& token : scanner) {
        std::cout << "Token: " << token << std::endl;
    }
    scanner.scan_classic();
    for (const auto& token : scanner) {
        std::cout << "Token: " << token << std::endl;
    }
}

void test_02_03()
{
    Scanner<int> scanner;
    scanner.set("123 + 234 * (345 % 456 / 567) / 678 - 789");
    scanner.scan();
    for (const auto& token : scanner) {
        std::cout << "Token: " << token << std::endl;
    }
    std::cout << std::endl;
    scanner.scan_classic();
    for (const auto& token : scanner) {
        std::cout << "Token: " << token << std::endl;
    }
}

// testing postfix calculator
void test_03_01()
{
    Scanner<long long> scanner;
    scanner.set("1 2 - 3 -");

    scanner.scan();
    for (const auto& token : scanner) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator<long long> calculator;
    auto result = calculator.calc(std::begin(scanner), std::end(scanner));
    std::cout << "Result: " << result << std::endl;
}

// testing postfix calculator without scanner
void test_03_02()
{
    // postfix: 1 2 - 3 - (infix: 1 - 2 - 3)
    Token<long long> t1{ 1 };
    Token<long long> t2{ 2 };
    Token<long long> t3{ OperatorType::SubOp };
    Token<long long> t4{ 3 };
    Token<long long> t5{ OperatorType::SubOp };

    std::list<Token<long long>> tokens;
    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);
    tokens.push_back(t4);
    tokens.push_back(t5);

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const auto& token : tokens) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    // calculate result of postfix expression
    PostfixCalculator<long long> calculator;
    auto result = calculator.calc(std::begin(tokens), std::end(tokens));
    std::cout << "Result: " << result << std::endl;
}

// testing postfix calculator with scanner
void test_03_03()
{
    // sum of first ten numbers
    Scanner<int> scanner;
    scanner.set("0 1 2 3 4 5 6 7 8 9 + + + + + + + + +");
    scanner.scan();

    PostfixCalculator<int> calculator;
    int result = calculator.calc(scanner.begin(), scanner.end());
    std::cout << "Result: " << result << std::endl;
}

void test_03_04()
{
    Token<short> t1 { 2 };
    Token<short> t2 { 4 };
    Token<short> t3 { 5 };
    Token<short> t4 { OperatorType::AddOp };
    Token<short> t5 { OperatorType::MulOp };
    Token<short> t6 { 3 };
    Token<short> t7 { OperatorType::DivOp };

    std::list<Token<short>> tokens;
    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);
    tokens.push_back(t4);
    tokens.push_back(t5);
    tokens.push_back(t6);
    tokens.push_back(t7);

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const auto& token : tokens) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    // calculate result of postfix expression
    PostfixCalculator<short> calculator;
    int result = calculator.calc(std::begin(tokens), std::end(tokens));
    std::cout << "Result: " << result << std::endl;
}

void test_04_01()
{
    // createPowerOf2PostfixExpression

    constexpr size_t MaxPower = 16;

    for (size_t n{1}; n != MaxPower; ++n) {

        // construct scan string for powers of '2'
        std::string s{};
        for (size_t i{}; i != n; ++i) {
            s.append("2 ");
        }
        for (size_t i{}; i != n - 1; ++i) {
            s.append("* ");
        }

        // compute value
        Scanner<int> scanner;
        scanner.set(s);
        scanner.scan();

        PostfixCalculator<int> calculator;
        int result = calculator.calc(scanner.begin(), scanner.end());
        std::cout << scanner.get() << " ==> " << result << std::endl;
    }
}

// testing infix to postfix converter
void test_10_01()
{
    // infix expression: 5 + 7
    std::list<Token<int>> infix 
    {
        { 5 },
        { OperatorType::AddOp },
        { 7 } 
    };

    // print postfix notation to stdout
    std::cout << "Infix Expression: " << std::endl;
    for (const auto& token : infix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    InfixToPostfixConverter<int> conv;
    std::list<Token<int>> postfix = conv.convert(std::begin(infix), std::end(infix));

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const auto& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator<int> calculator;
    int result = calculator.calc(std::begin(postfix), std::end(postfix));
    std::cout << "Result: " << result << std::endl;
}

void test_10_02()
{
    // infix expression: 2 * 3 / (2 - 1) + 5 * (4 - 1)
    std::list<Token<int>> infix{
        { 2 },
        { OperatorType::MulOp },
        { 3 },
        { OperatorType::DivOp },

        { TokenType::LBracket },
        { 2 },
        { OperatorType::SubOp },
        { 1 },
        { TokenType::RBracket },

        { OperatorType::AddOp },
        { 5 },
        { OperatorType::MulOp },

        { TokenType::LBracket },
        { 4 },
        { OperatorType::SubOp },
        { 1 },
        { TokenType::RBracket }
    };

    // print postfix notation to stdout
    std::cout << "Infix Expression: " << std::endl;
    for (const auto& token : infix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    InfixToPostfixConverter<int> conv;
    std::list<Token<int>> postfix = conv.convert(std::begin(infix), std::end(infix));

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token<int>& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator<int> calculator;
    int result = calculator.calc(std::begin(postfix), std::end(postfix));
    std::cout << "Result: " << result << std::endl;
}

void test_10_03()
{
    Scanner<int> scanner;
    scanner.set("2 * 3 / (2 - 1) + 5 * (4 - 1)");
    scanner.scan();

    // print postfix notation to stdout
    std::cout << "Infix Expression:   ";
    for (const Token<int>& token : scanner) {
        std::cout << token << ' ';
    }
    std::cout << std::endl << std::endl;

    InfixToPostfixConverter<int> conv;
    std::list<Token<int>> postfix = conv.convert(std::begin(scanner), std::end(scanner));

    // print postfix notation to stdout
    std::cout << "Postfix Expression: ";
    for (const Token<int>& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator<int> calculator;
    int result = calculator.calc(std::begin(postfix), std::end(postfix));
    std::cout << "Result: " << result << std::endl;
}

void test_10_04()
{
    Scanner<int> scanner;
    scanner.set("2 * (4 + 5) / 3");
    scanner.scan();

    // print postfix notation to stdout
    std::cout << "Infix Expression: " << std::endl;
    for (const Token<int>& token : scanner) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    InfixToPostfixConverter<int> conv;
    std::list<Token<int>> postfix = conv.convert(std::begin(scanner), std::end(scanner));

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token<int>& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator<int> calculator;
    int result = calculator.calc(std::begin(postfix), std::end(postfix));
    std::cout << "Result: " << result << std::endl;
}

void test_10_05()
{
    Scanner<int> scanner;
    scanner.set("(3 + 7) / (4 - 2)");
    scanner.scan();

    // print postfix notation to stdout
    std::cout << "Infix Expression: " << std::endl;
    for (const Token<int>& token : scanner) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    InfixToPostfixConverter<int> conv;
    std::list<Token<int>> postfix = conv.convert(std::begin(scanner), std::end(scanner));

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token<int>& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator<int> calculator;
    int result = calculator.calc(std::begin(postfix), std::end(postfix));
    std::cout << "Result: " << result << std::endl;
}

void test_10_06()
{
    Scanner<double> scanner;
    scanner.set("2 * (4 + 5) / 3");
    scanner.scan();

    // print postfix notation to stdout
    std::cout << "Infix Expression: " << std::endl;
    for (const Token<double>& token : scanner) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    InfixToPostfixConverter<double> conv;
    std::list<Token<double>> postfix = conv.convert(std::begin(scanner), std::end(scanner));

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token<double>& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator<double> calculator;
    double result = calculator.calc(std::begin(postfix), std::end(postfix));
    std::cout << "Result: " << result << std::endl;
}

int main()
{
    // testing tokens
    test_01_01();
    test_01_02();

    // testing scanner
    test_02_01();
    test_02_02();
    test_02_03();

    // testing postfix calculator
    test_03_01();
    test_03_02();
    test_03_03();
    test_03_04();

    // createPowerOf2PostfixExpression
    test_04_01();

    // testing infix to postfix converter
    test_10_01();
    test_10_02();
    test_10_03();
    test_10_04();
    test_10_05();
    test_10_06();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
