// =====================================================================================
// UPN.cpp
// =====================================================================================

#include <iostream>
#include <list>
#include <stack>
#include <string>

#include "UPN.h"

Token::Token() : m_type{ TokenType ::Null}, m_op{ OperatorType::NullOp } {}
Token::Token(TokenType type) : m_type{ type }, m_op{ OperatorType::NullOp } {}
Token::Token(TokenType type, OperatorType op) : m_type{ type }, m_op{ op } {}

// ?????????????????????
// Token::Token(TokenType type, int value) : m_type{ TokenType::Null }, m_op{ OperatorType::NullOp } {}  


std::ostream& operator<< (std::ostream& os, const Token& tok)
{
    switch (tok.m_type)
    {
    case TokenType::Operand:
        os << tok.m_value;
        break;
    case TokenType::Operator:
        switch (tok.m_op)
        {
        case OperatorType::AddOp:
            os << '+';
            break;
        case OperatorType::SubOp:
            os << '-';
            break;
        case OperatorType::MulOp:
            os << '*';
            break;
        case OperatorType::DivOp:
            os << '/';
            break;
        case OperatorType::ModOp:
            os << '%';
            break;
        }
        break;
    case TokenType::LBracket:
        os << '(';
        break;
    case TokenType::RBracket:
        os << ')';
        break;
    }

    os << ' ';
    return os;
}


void Scanner::setLine(const std::string& line)
{
    m_line = line;
}

int Scanner::length()
{
    return 0; //TODO ????
}

void Scanner::scan()
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
}


int PostfixCalculator::calculate(std::list<Token> postfix)
{
    std::stack<Token> m_stack;  // temporary stack of operands

    std::list<Token>::iterator it;

    for (it = postfix.begin(); it != postfix.end(); it++)
    {
        Token tok = *it;

        if (tok.GetTokenType() == TokenType::Operand)
        {
            // push operand on temporary operand stack
            m_stack.push(tok);
        }
        else if (tok.GetTokenType() == TokenType::Operator)
        {
            // binary operator, retrieve operands from operand stack
            Token right{ m_stack.top() };
            m_stack.pop();

            Token left{ m_stack.top() };
            m_stack.pop();

            int rightValue{ right.getValue() };
            int leftValue{ left.getValue() };
            int result{};

            OperatorType op{ tok.GetOperatorType() };
            switch (op)
            {
            case OperatorType::AddOp:
                result = leftValue + rightValue;
                break;
            case OperatorType::SubOp:
                result = leftValue - rightValue;
                break;
            case OperatorType::MulOp:
                result = leftValue * rightValue;
                break;
            case OperatorType::DivOp:
                result = leftValue / rightValue;
                break;
            case OperatorType::ModOp:
                result = leftValue % rightValue;
                break;
            }

            // push result to operand stack
            Token val(TokenType::Operand, result);
            m_stack.push(val);
        }
    }

    // retrieve result from stack
    Token result{ m_stack.top() };
    m_stack.pop();
    return result.getValue();
}

// =====================================================================================
// End-of-File
// =====================================================================================
