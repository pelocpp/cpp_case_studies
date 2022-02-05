// =====================================================================================
// PostfixCalculator.h
// =====================================================================================

#pragma once

class PostfixCalculator
{
private:
    std::stack<Token> m_stack;  // temporary stack of operands

public:
    // c'tor

    // public interface
    int calc(std::list<Token> postfix);
    //int Calculate(TokenList postfix);
    //int CalculateEx(TokenList postfix);
};

// =====================================================================================
// End-of-File
// =====================================================================================
