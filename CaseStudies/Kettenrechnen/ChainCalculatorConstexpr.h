// =====================================================================================
// ChainCalculatorClassic.h
// =====================================================================================

#pragma once

#include <iostream>
#include <string>

namespace ChainArithmetic_Constexpr {

    enum class TokenType { Null, Operator, Operand };

    enum class OperatorType { NullOp, AddOp, SubOp, MulOp, DivOp };

    using OperandType = signed long long;

    class Token
    {
    private:
        // member data
        TokenType     m_type;     // classification of token
        OperatorType  m_op;       // classification of operator (TokenType == Operator)
        OperandType   m_value;    // value of constant (TokenType == Operand)

    public:
        // c'tor(s)
        constexpr Token();
        constexpr Token(OperatorType op);
        constexpr Token(OperandType value);

        // getter
        constexpr TokenType getTokenType() const;
        constexpr OperatorType getOperatorType() const;
        constexpr OperandType getValue() const;
    };

    class ChainCalculatorConstexpr
    {
    public:
        // public interface
        constexpr static OperandType calc(const char* expression);

    private:
        // private helper methods
        constexpr static bool isDigit(const char);
        constexpr static Token getNextToken(const char**);
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
