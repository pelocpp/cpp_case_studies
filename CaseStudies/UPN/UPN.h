// =====================================================================================
// UPN.h
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

class Scanner
{
    // Hmmmm, macht der wirklich Sinn ????
    friend std::ostream& operator<< (std::ostream&, const Scanner&);

private:
    std::string m_line;

    // ODER Std::vector ... oder std::forward_list ???
    std::list<Token> m_tokens;

public:
    // c'tor(s)
    //Scanner();

    // setter
    void setLine(const std::string&);
    int length ();

    // public interface
    //bool hasMoreExpressions();
    //void readLine();
    std::list<Token> scan();

};

class PostfixCalculator
{
private:
    std::stack<Token> m_stack;  // temporary stack of operands

    // IntegerStack m_stack;  // temporary stack of operands

public:
    // c'tor

    // public interface
    int calculate(std::list<Token> postfix);
    //int Calculate(TokenList postfix);
    //int CalculateEx(TokenList postfix);
};


// =====================================================================================
// End-of-File
// =====================================================================================
