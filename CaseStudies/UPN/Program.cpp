// =====================================================================================
// Program.cpp / Umgekehrte Polnische Notation (UPN)
// =====================================================================================

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <regex>

#include "Token.h"
#include "Scanner.h"
#include "PostfixCalculator.h"
#include "InfixToPostfixConverter.h"


// TODO: Modulo OPerator ergänzen ...

    // TODO : testen, ob man das das Objekt verändern kann (also die Zeichenkette..=
//const std::string& get() const {
//    return m_line;
//}

// testing tokens
void test_01()
{
    Token<size_t> tok1{ TokenType::LBracket };
    Token<size_t> tok2{ TokenType::RBracket };
    Token<size_t> tok3{ TokenType::Operator, OperatorType::AddOp };
    Token<size_t> tok4{ TokenType::Operand, 12345 };

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
    Token<long long> t1{ TokenType::Operand, 1 };
    Token<long long> t2{ TokenType::Operand, 2 };
    Token<long long> t3{ TokenType::Operator, OperatorType::SubOp };
    Token<long long> t4{ TokenType::Operand, 3 };
    Token<long long> t5{ TokenType::Operator, OperatorType::SubOp };

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




void test_20_simple_regex()
{
    // simple example

  //  std::regex re{ "\\(|\\)|+|\\-|*|/|[[digit]]+" };

   // std::regex re{ "\\d+" };   // Geht
   // std::regex re{ "[1-9][0-9]+" };   //  // Geht für 345345
  //   std::regex re{ "([1-9][0-9]+)|\\*|\\+" };   // Geht für 345345 ODER + ODER -
  //  std::regex re{ "^(([1-9][0-9]+)|\\*|\\+)+$" };   // Geht für 345345 UND + UND -
    // std::regex re{ "^(([1-9][0-9]+)|\\+|\\-|\\*|\\/)+$" };   // Geht für ALLES OHNE KLAMMERN

    // std::regex re{ "^([(]|[)])+$" };   // Geht für KLAMMERN

     std::regex re{ "^(([1-9][0-9]*)|[(]|[)]|\\+|\\-|\\*|\\/)+$" };   // Geht für ALLES OHNE KLAMMERN

    // extract blanks !!!
    std::string test{ "1+22*(4444-5555)" };

    bool result{ std::regex_match(test, re) };
    std::cout << std::boolalpha << test << ": " << result << std::endl;

}

void test_21_simple_regex()
{
    std::string s = "123 apples 456 oranges 789 bananas oranges bananas";

    std::regex words_regex("[a-z]+");

    for (std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), words_regex);
        i != std::sregex_iterator();
        ++i)
    {
        std::smatch m = *i;
        std::cout << m.str() << " at position " << m.position() << '\n';
    }
}

void test_22_simple_regex()
{
    std::string s = "1 + 22 * ( 4444 - 5555)";

    std::regex token_regex("([1-9][0-9]*)|[(]|[)]|\\+|\\-|\\*|\\/");

    auto rbegin = std::sregex_iterator(
        std::begin(s),
        std::end(s),
        token_regex
    );

    auto rend = std::sregex_iterator();

    while (rbegin != rend)
    {
        std::smatch m = *rbegin;
        std::string token = m.str();

        std::cout << "At position " << m.position() << ": " << token << std::endl;
        ++rbegin;
    }
}

void test_23_simple_regex()
{
    std::string s = "1+22*(4444-5555)";

    std::regex regex("(([1-9][0-9]*)|[(]|[)]|\\+|\\-|\\*|\\/)+");

    std::smatch matches;

    if (std::regex_search(s, matches, regex)) {

        std::cout << "Match found\n";

        for (size_t i = 0; i < matches.size(); ++i) {
            std::cout << i << ": '" << matches[i].str() << "'\n";
        }
    }
    else {
        std::cout << "Match not found\n";
    }
}

void test_24_simple_regex()
{
    std::string s = "1+22*(4444-5555)";

    std::regex regex("([1-9][0-9]*)|[(]|[)]|\\+|\\-|\\*|\\/");

    std::smatch matches;

    while (std::regex_search(s, matches, regex)) { //loop

        std::cout << "A:" << matches[0] << std::endl;

        s = matches.suffix(); //remove "192", then "168" ...
    }
}


int main()
{
    //test_01();
    //test_02_01();
    //test_02_02();
    test_02_03();
    //test_03_01();
    //test_03_02();
    //test_03_03();
    //test_03_04();

    //test10_01();
    //test10_02();
    //test10_03();
    //test10_04();
    //test10_05();

    //test_20_simple_regex();
   //test_21_simple_regex();
   //test_22_simple_regex();
   //test_24_simple_regex();


    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
