// =====================================================================================
// Token.h
// =====================================================================================

#pragma once

#include <iostream>

enum class TokenType { Null, Operator, Operand };

enum class OperatorType { NullOp, AddOp, SubOp, MulOp, DivOp };

using OperandType = signed long long;

template <typename T>
class Token;

template <typename T>
std::ostream& operator<< (std::ostream&, const Token<T>&);

template <typename T>
class Token
{
    // Warum wird das nicht gebraucht ??????????????????????????????????
    friend std::ostream& operator<< <> (std::ostream&, const Token<T>&);

    // wird nirgends aufgerufen !!!!!!!!!!!!!!!!!!!!!!!!!!

private:
    // member data
    TokenType m_type;      // classification of token
    OperatorType m_op;     // classification of operator (TokenType == Operator)
    T m_value;             // value of constant (TokenType == Operand)

public:
    // c'tor(s)
    Token() : Token(TokenType::Null, OperatorType::NullOp, T{}) {}

    Token(TokenType type) : Token(type, OperatorType::NullOp, T{}) {}

    Token(OperatorType op) : Token(TokenType::Operator, op, T{}) {}

    Token(T value) : Token(TokenType::Operand, OperatorType::NullOp, value) {}

    // getter
    TokenType getTokenType() const { return m_type; }
    OperatorType getOperatorType() const { return m_op; }
    T getValue() const { return m_value; }

private:
    // general purpose c'tor
    Token(TokenType type, OperatorType op, T value)
        : m_type{ type }, m_op{ op }, m_value{ value } {}
};

template <typename T>
std::ostream& operator<< (std::ostream& os, const Token<T>& tok)
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
        case OperatorType::NullOp:
            break;
        }
        break;

    default:
        os << ' ';  // suited for debugging output
        break;
    }

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
