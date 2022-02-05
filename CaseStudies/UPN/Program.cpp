// =====================================================================================
// Program.cpp / Umgekehrte Polnische Notation (UPN)
// =====================================================================================

#include <iostream>
#include <list>
#include <stack>
#include <string>

#include "Token.h"
#include "Scanner.h"
#include "PostfixCalculator.h"
#include "InfixToPostfixConverter.h"

// TODO:
// Geht das Scanning mit einem Reg Expr ?!?!?!

// testing tokens
void test_01()
{
    Token tok1{ TokenType::LBracket };
    Token tok2{ TokenType::RBracket };
    Token tok3{ TokenType::Operator, OperatorType::AddOp };
    Token tok4{ TokenType::Operand, 12345 };

    std::cout << tok1 << std::endl;
    std::cout << tok2 << std::endl;
    std::cout << tok3 << std::endl;
    std::cout << tok4 << std::endl;
}

// testing scanner
void test_02_01()
{
    Scanner scanner;
    scanner.set("1 2 *");
    std::cout << scanner << std::endl;
}

void test_02_02()
{
    Scanner scanner;
    scanner.set("1 2 - 3 -");
    std::cout << scanner << std::endl << std::endl;

    std::list<Token> tokens = scanner.scan();
    for (const Token& token : tokens)
        std::cout << "Token: " << token << std::endl;
}

// testing postfix calculator
void test_03_01()
{
    Scanner scanner;
    scanner.set("1 2 - 3 -");

    std::list<Token> postfix = scanner.scan();
    for (const Token& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator calculator;
    int result = calculator.calc(postfix);
    std::cout << "Result: " << result << std::endl;
}

// testing postfix calculator without scanner
void test_03_02()
{
    // postfix: 1 2 - 3 - (infix: 1 - 2 - 3)
    Token t1{ TokenType::Operand, 1 };
    Token t2{ TokenType::Operand, 2 };
    Token t3{ TokenType::Operator, OperatorType::SubOp };
    Token t4{ TokenType::Operand, 3 };
    Token t5{ TokenType::Operator, OperatorType::SubOp };

    std::list<Token> tokens;
    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);
    tokens.push_back(t4);
    tokens.push_back(t5);

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token& token : tokens) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    // calculate result of postfix expression
    PostfixCalculator calculator;
    int result = calculator.calc(tokens);
    std::cout << "Result: " << result << std::endl;
}

// testing postfix calculator with scanner
void test_03_03()
{
    // sum of first ten numbers
    Scanner scanner;
    scanner.set("0 1 2 3 4 5 6 7 8 9 + + + + + + + + +");

    std::list<Token> postfix = scanner.scan();

    PostfixCalculator calculator;
    int result = calculator.calc(postfix);
    std::cout << "Result: " << result << std::endl;
}

void test_03_04()
{
    Token t1 { TokenType::Operand, 2 };
    Token t2 { TokenType::Operand, 4 };
    Token t3 { TokenType::Operand, 5 };
    Token t4 { TokenType::Operator, OperatorType::AddOp };
    Token t5 { TokenType::Operator, OperatorType::MulOp };
    Token t6 { TokenType::Operand, 3 };
    Token t7 { TokenType::Operator, OperatorType::DivOp };

    std::list<Token> tokens;
    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);
    tokens.push_back(t4);
    tokens.push_back(t5);
    tokens.push_back(t6);
    tokens.push_back(t7);

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token& token : tokens) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    // calculate result of postfix expression
    PostfixCalculator calculator;
    int result = calculator.calc(tokens);
    std::cout << "Result: " << result << std::endl;
}

// =====================================================================================

void test10_01()
{
    // infix expression: 5 + 7
    std::list<Token> infix {
        { TokenType::Operand, 5 },
        { TokenType::Operator, OperatorType::AddOp },
        { TokenType::Operand, 7 } 
    };

    // print postfix notation to stdout
    std::cout << "Infix Expression: " << std::endl;
    for (const Token& token : infix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    InfixToPostfixConverter conv;
    std::list<Token> postfix = conv.convert(infix);

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator calculator;
    int result = calculator.calc(postfix);
    std::cout << "Result: " << result << std::endl;
}

void test10_02()
{
    // infix expression: 2 * 3 / (2 - 1) + 5 * (4 - 1)
    std::list<Token> infix{
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
    for (const Token& token : infix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    InfixToPostfixConverter conv;
    std::list<Token> postfix = conv.convert(infix);

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator calculator;
    int result = calculator.calc(postfix);
    std::cout << "Result: " << result << std::endl;
}

void test10_03()
{
    Scanner scanner;
    scanner.set("2 * 3 / (2 - 1) + 5 * (4 - 1)");
    std::list<Token> infix = scanner.scan();

    // print postfix notation to stdout
    std::cout << "Infix Expression: " << std::endl;
    for (const Token& token : infix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl << std::endl;

    InfixToPostfixConverter conv;
    std::list<Token> postfix = conv.convert(infix);

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator calculator;
    int result = calculator.calc(postfix);
    std::cout << "Result: " << result << std::endl;
}

void test10_04()
{
    Scanner scanner;
    scanner.set("2 * (4 + 5) / 3");
    std::list<Token> infix = scanner.scan();

    // print postfix notation to stdout
    std::cout << "Infix Expression: " << std::endl;
    for (const Token& token : infix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    InfixToPostfixConverter conv;
    std::list<Token> postfix = conv.convert(infix);

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator calculator;
    int result = calculator.calc(postfix);
    std::cout << "Result: " << result << std::endl;
}

void test10_05()
{
    Scanner scanner;
    scanner.set("(3 + 7) / (4 - 2)");
    std::list<Token> infix = scanner.scan();

    // print postfix notation to stdout
    std::cout << "Infix Expression: " << std::endl;
    for (const Token& token : infix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    InfixToPostfixConverter conv;
    std::list<Token> postfix = conv.convert(infix);

    // print postfix notation to stdout
    std::cout << "Postfix Expression: " << std::endl;
    for (const Token& token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator calculator;
    int result = calculator.calc(postfix);
    std::cout << "Result: " << result << std::endl;
}
int main()
{
    //test_01();
    //test_02_01();
    //test_02_02();
    //test_03_01();
    //test_03_02();
    //test_03_03();
    //test04();
    //test04_01();
    // test_03_04();

    //test10_01();
    //test10_02();
    test10_03();
    //test10_04();
    //test10_05();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
