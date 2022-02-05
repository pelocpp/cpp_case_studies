// =====================================================================================
// InfixToPostfixConverter.h
// =====================================================================================

#pragma once

class InfixToPostfixConverter
{
private:
    std::list<Token> m_infix;          // infix expression (input)
    std::list<Token> m_postfix;        // postfix expression (output)

    std::stack<Token> m_stack;         // temporary stack of operators and brackets

    Token m_tok;                  // current token
    // int m_curToken;            // index of current token
    std::list<Token>::iterator m_it;   // iterator to address the infix list


public:
    // public interface
    std::list<Token> convert(std::list<Token> infix);

private:
    // helper methods
    void clear();
    Token nextToken();

    void processOperand();
    void processOperator();
    void processLeftParenthesis();
    void processRightParenthesis();
    void processEndOfInput();

    void dumpStacks();
};

// =====================================================================================
// End-of-File
// =====================================================================================
