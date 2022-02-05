// =====================================================================================
// Token.cpp
// =====================================================================================

#include <iostream>
#include <string>

#include "Token.h"

Token::Token() 
    : m_type{ TokenType::Null }, m_op{ OperatorType::NullOp }, m_value{}, m_precedence{} {}

Token::Token(TokenType type) 
    : m_type{ type }, m_op{ OperatorType::NullOp }, m_value{}, m_precedence{}  {}

Token::Token(TokenType type, OperatorType op)
    : m_type{ type }, m_op{ op }, m_value{} 
{
    switch (op)
    {
    case OperatorType::NullOp:
        m_precedence = 0;
        break;
    case OperatorType::AddOp:
    case OperatorType::SubOp:
        m_precedence = 1;
        break;
    case OperatorType::MulOp:
    case OperatorType::DivOp:
    case OperatorType::ModOp:
        m_precedence = 2;
        break;
    }
}

Token::Token(TokenType type, int value)
    : m_type{ TokenType::Operand }, m_op{ OperatorType::NullOp }, m_value{ value }, m_precedence{} {}

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

    default:
        os << ' ';  // better suited for debugging output
        break;
    }

    return os;
}
// =====================================================================================
// End-of-File
// =====================================================================================
