// =====================================================================================
// Program.cpp / Umgekehrte Polnische Notation (UPN)
// =====================================================================================

#include <iostream>
#include <list>
#include <stack>
#include <string>

#include "UPN.h"


// TODO:
// Geht das Scanning mit einem Reg Expr ?!?!?!

// testing tokens
void test01a()
{
    Token tok1;
    Token tok2(TokenType::LBracket);
    Token tok3(TokenType::RBracket);
    Token tok4(TokenType::Operator, OperatorType::AddOp);
    Token tok5(TokenType::Operand, 12345);

    std::cout << '>' << tok1 << '<' << std::endl;
    std::cout << tok2 << std::endl;
    std::cout << tok3 << std::endl;
    std::cout << tok4 << std::endl;
    std::cout << tok5 << std::endl;
}

void test01b()
{
    Token tok1;
    Token tok2(TokenType::Operator, OperatorType::AddOp);
    Token tok3(TokenType::Operand, 12345);

    std::cout << '>' << tok1 << '<' << std::endl;
    std::cout << tok2 << std::endl;
    std::cout << tok3 << std::endl;
}

void test04a()
{
    // sum of first ten numbers
    Scanner scanner;
    scanner.setLine("2 3 *");

    std::list<Token> postfix = scanner.scan();

    PostfixCalculator calc;
    int result = calc.calculate(postfix);
    std::cout << "Result: " << result << std::endl;
}

void test04b()
{
    // sum of first ten numbers
    Scanner scanner;
    scanner.setLine("0 1 2 3 4 5 6 7 8 9 + + + + + + + + +");

    std::list<Token> postfix = scanner.scan();

    PostfixCalculator calc;
    int result = calc.calculate(postfix);
    std::cout << "Result: " << result << std::endl;
}


int main()
{
    std::cout << "UPN: " << std::endl;
    test04a();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
