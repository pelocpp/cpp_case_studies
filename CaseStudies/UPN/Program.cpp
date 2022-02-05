// =====================================================================================
// Program.cpp / Umgekehrte Polnische Notation (UPN)
// =====================================================================================

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

#include "Token.h"
#include "Scanner.h"
#include "PostfixCalculator.h"
#include "InfixToPostfixConverter.h"

// TODO:
// Geht das Scanning mit einem Reg Expr ?!?!?!


using ValueType = long;

// testing tokens
void test_01()
{
    Token<ValueType> tok1{ TokenType::LBracket };
    Token<ValueType> tok2{ TokenType::RBracket };
    Token<ValueType> tok3{ TokenType::Operator, OperatorType::AddOp };
    Token<ValueType> tok4{ TokenType::Operand, 12345 };

    std::cout << tok1 << std::endl;
    std::cout << tok2 << std::endl;
    std::cout << tok3 << std::endl;
    std::cout << tok4 << std::endl;
}

void test_01a()
{
    Token<int> tok1{ TokenType::LBracket };
    Token<int> tok2{ TokenType::RBracket };
    Token<int> tok3{ TokenType::Operator, OperatorType::AddOp };
    Token<int> tok4{ TokenType::Operand, 12345 };

    std::cout << tok1 << std::endl;
    std::cout << tok2 << std::endl;
    std::cout << tok3 << std::endl;
    std::cout << tok4 << std::endl;
}

// testing scanner
void test_02_01()
{
    Scanner<ValueType> scanner;
    scanner.set("1 2 *");
    std::cout << scanner.get() << std::endl;
}

void test_02_02()
{
    Scanner<ValueType> scanner;
    scanner.set("1 2 - 3 -");
    scanner.scan();
    for (const auto& token : scanner)
        std::cout << "Token: " << token << std::endl;
}

// testing postfix calculator
void test_03_01()
{
    Scanner<ValueType> scanner;
    scanner.set("1 2 - 3 -");

    scanner.scan();
    for (const auto& token : scanner) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator<ValueType> calculator;
    int result = calculator.calc(std::begin(scanner), std::end(scanner));
    std::cout << "Result: " << result << std::endl;
}

// testing postfix calculator without scanner
void test_03_02()
{
    // postfix: 1 2 - 3 - (infix: 1 - 2 - 3)
    Token<ValueType> t1{ TokenType::Operand, 1 };
    Token<ValueType> t2{ TokenType::Operand, 2 };
    Token<ValueType> t3{ TokenType::Operator, OperatorType::SubOp };
    Token<ValueType> t4{ TokenType::Operand, 3 };
    Token<ValueType> t5{ TokenType::Operator, OperatorType::SubOp };

    std::list<Token<ValueType>> tokens;
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
    PostfixCalculator<ValueType> calculator;
    int result = calculator.calc(std::begin(tokens), std::end(tokens));
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
    Token<short> t1 { TokenType::Operand, 2 };
    Token<short> t2 { TokenType::Operand, 4 };
    Token<short> t3 { TokenType::Operand, 5 };
    Token<short> t4 { TokenType::Operator, OperatorType::AddOp };
    Token<short> t5 { TokenType::Operator, OperatorType::MulOp };
    Token<short> t6 { TokenType::Operand, 3 };
    Token<short> t7 { TokenType::Operator, OperatorType::DivOp };

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


//// =====================================================================================
//
void test10_01()
{
    // infix expression: 5 + 7
    std::list<Token<int>> infix 
    {
        { TokenType::Operand, 5 },
        { TokenType::Operator, OperatorType::AddOp },
        { TokenType::Operand, 7 } 
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

void test10_02()
{
    // infix expression: 2 * 3 / (2 - 1) + 5 * (4 - 1)
    std::list<Token<int>> infix{
        { TokenType::Operand, 2 },
        { TokenType::Operator, OperatorType::MulOp },
        { TokenType::Operand, 3 },
        { TokenType::Operator, OperatorType::DivOp },

        { TokenType::LBracket },
        { TokenType::Operand, 2 },
        { TokenType::Operator, OperatorType::SubOp },
        { TokenType::Operand, 1 },
        { TokenType::RBracket },

        { TokenType::Operator, OperatorType::AddOp },
        { TokenType::Operand, 5 },
        { TokenType::Operator, OperatorType::MulOp },

        { TokenType::LBracket },
        { TokenType::Operand, 4 },
        { TokenType::Operator, OperatorType::SubOp },
        { TokenType::Operand, 1 },
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

void test10_03()
{
    Scanner<int> scanner;
    scanner.set("2 * 3 / (2 - 1) + 5 * (4 - 1)");
    scanner.scan();

    // print postfix notation to stdout
    std::cout << "Infix Expression: " << std::endl;
    for (const Token<int>& token : scanner) {
        std::cout << token << ' ';
    }
    std::cout << std::endl << std::endl;

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

void test10_04()
{
    Scanner<int> scanner;
    scanner.set("2 * (4 + 5) / 3");
    // std::list<Token<int>> infix = scanner.scan();
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

void test10_05()
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




int main()
{
    test_01();
    test_02_01();
    test_02_02();
    test_03_01();
    test_03_02();
    test_03_03();
    test_03_04();

    test10_01();  //  TODO DIE KRACHT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    test10_02();
    test10_03();
    test10_04();
    test10_05();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
