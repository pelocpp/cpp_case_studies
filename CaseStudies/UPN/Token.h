// =====================================================================================
// Token.h
// =====================================================================================

#pragma once

enum class TokenType { Null, Operator, Operand, LBracket, RBracket };

enum class OperatorType { NullOp, AddOp, SubOp, MulOp, DivOp, ModOp };

template <typename T>
class Token;

template <typename T>
std::ostream& operator<< (std::ostream&, const Token<T>&);

template <typename T>
class Token
{
    friend std::ostream& operator<< <> (std::ostream&, const Token<T>&);

private:
    // member data
    TokenType m_type;      // classification of token
    OperatorType m_op;     // classification of operator (TokenType == Operator)
    T m_value;           // value of constant (TokenType == Constant)
    size_t m_precedence;   // precedence of this operator, if any 

public:
    // c'tor(s)
    Token() : Token(TokenType::Null, OperatorType::NullOp, T{}) {}

    Token(TokenType type) : Token(type, OperatorType::NullOp, T{}) {}

    Token(TokenType type, OperatorType op) : Token(type, op, T{}) {}

    Token(TokenType type, T value) : Token(type, OperatorType::NullOp, value) {}

    // getter
    TokenType getTokenType() const { return m_type; }
    OperatorType getOperatorType() const { return m_op; }
    T getValue() const { return m_value; }
    size_t getPrecedence() const { return m_precedence; }

private:
    // general purpose c'tor
    Token(TokenType type, OperatorType op, T value) 
        : m_type{ type }, m_op{ op }, m_value{ value } 
    {
        switch (op)
        {
        case OperatorType::AddOp:
        case OperatorType::SubOp:
            m_precedence = 1;
            break;
        case OperatorType::MulOp:
        case OperatorType::DivOp:
        case OperatorType::ModOp:
            m_precedence = 2;
            break;
        default:
            m_precedence = 0;
        }
    }
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
        case OperatorType::ModOp:
            os << '%';
            break;
        case OperatorType::NullOp:
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
        os << ' ';  // suited for debugging output
        break;
    }

    return os;
}


// =====================================================================================
// End-of-File
// =====================================================================================
