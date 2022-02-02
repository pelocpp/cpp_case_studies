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
    for (Token token : tokens)
        std::cout << "Token: " << token << std::endl;
}

// testing postfix calculator
void test_03_01()
{
    Scanner scanner;
    scanner.set("1 2 - 3 -");

    std::list<Token> postfix = scanner.scan();
    for (Token token : postfix) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    PostfixCalculator calc;
    int result = calc.calc(postfix);
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
    for (Token token : tokens) {
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

    PostfixCalculator calc;
    int result = calc.calc(postfix);
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
    for (Token token : tokens) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    // calculate result of postfix expression
    PostfixCalculator calculator;
    int result = calculator.calc(tokens);
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
    test_03_04();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
