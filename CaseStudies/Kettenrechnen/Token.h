// =====================================================================================
// Token.h
// =====================================================================================

#pragma once

#include <iostream>

enum class TokenType { Null, Operator, Operand };

enum class OperatorType { NullOp, AddOp, SubOp, MulOp, DivOp };

using OperandType = signed long long;

template <typename T>
class Token
{
private:
    // member data
    TokenType     m_type;     // classification of token
    OperatorType  m_op;       // classification of operator (TokenType == Operator)
    T             m_value;    // value of constant (TokenType == Operand)

public:
    // c'tor(s)
    Token() 
        : m_type{ TokenType::Null }, m_op{ OperatorType::NullOp }, m_value{ T{} } 
    {}

    Token(OperatorType op) 
        : m_type{ TokenType::Operator }, m_op{ op }, m_value{ T{} }
    {}

    Token(T value)
        : m_type { TokenType::Operand }, m_op{ OperatorType::NullOp }, m_value{ value }
    {}

    // getter
    TokenType getTokenType() const { return m_type; }
    OperatorType getOperatorType() const { return m_op; }
    T getValue() const { return m_value; }
};

template <typename T>
std::ostream& operator<< (std::ostream& os, const Token<T>& tok)
{
    switch (tok.getTokenType())
    {
    case TokenType::Operand:
        os << tok.getValue();
        break;

    case TokenType::Operator:
        switch (tok.getOperatorType())
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
        case OperatorType::NullOp:
            break;
        }
        break;

    default:
        os << ' ';
        break;
    }

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
