// =====================================================================================
// Token.h
// =====================================================================================

#pragma once

enum class TokenType { Null, Operator, Operand, LBracket, RBracket };

enum class OperatorType { NullOp, AddOp, SubOp, MulOp, DivOp, ModOp };

class Token
{
    friend std::ostream& operator<< (std::ostream&, const Token&);

private:
    // member data
    TokenType m_type;    // classification of token
    OperatorType m_op;   // classification of operator (TokenType == Operator)
    int m_value;         // value of constant (TokenType == Constant)  // Könnte man mit Template machen ?!?!?
  //  int m_precedence;    // precedence of this operator, if any 
                         // TODO: wird m_precedence verwendet ???

public:
    // c'tor(s)
    Token();
    Token(TokenType type);
    Token(TokenType type, OperatorType op);
    Token(TokenType type, int value);

    // getter
    TokenType getTokenType() const { return m_type; }
    OperatorType getOperatorType() const { return m_op; }
    int getValue() const { return m_value; }
    //  int GetPrecedence() { return m_precedence; }
};

// =====================================================================================
// End-of-File
// =====================================================================================
