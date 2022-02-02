// =====================================================================================
// Scanner.cpp
// =====================================================================================

#include <iostream>
#include <list>
// #include <stack>
#include <string>

#include "Token.h"
#include "Scanner.h"

void Scanner::set(const std::string& line)
{
    m_line = line;
}

//int Scanner::length()
//{
//    return 0; //TODO ????
//}

std::list<Token> Scanner::scan()
{
    for (size_t i{}; i != m_line.size(); ++i)
    {
        char c{ m_line[i] };

        switch (c)
        {
        case ' ':
            continue;

        case '(':
        {
            Token tok(TokenType::LBracket);
            m_tokens.push_back(tok);
        }
        break;

        case ')':
        {
            Token tok(TokenType::RBracket);
            m_tokens.push_back(tok);
        }
        break;

        case '+':
        {
            Token tok(TokenType::Operator, OperatorType::AddOp);
            m_tokens.push_back(tok);
        }
        break;

        case '-':
        {
            Token tok(TokenType::Operator, OperatorType::SubOp);
            m_tokens.push_back(tok);
        }
        break;

        case '*':
        {
            Token tok(TokenType::Operator, OperatorType::MulOp);
            m_tokens.push_back(tok);
        }
        break;

        case '/':
        {
            Token tok(TokenType::Operator, OperatorType::DivOp);
            m_tokens.push_back(tok);
        }
        break;

        case '%':
        {
            Token tok(TokenType::Operator, OperatorType::ModOp);
            m_tokens.push_back(tok);
        }
        break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            int value{};
            while (i != m_line.size() && std::isdigit(m_line[i]))
            {
                value = 10 * value + (m_line[i] - '0');
                i++;
            }

            // adjust index
            i--;

            Token tok(TokenType::Operand, value);
            m_tokens.push_back(tok);
        }
        break;
        }
    }

    return m_tokens;
}

std::ostream& operator<< (std::ostream& os, const Scanner& scanner) {

    os << "Input: " << scanner.m_line;
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
