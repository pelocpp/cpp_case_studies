// =====================================================================================
// ChainCalculatorRegex.h
// =====================================================================================

#pragma once

#include <iostream>
#include <string>
#include <regex>

#include "Token.h"

namespace ChainArithmetic_Regex {

    class ChainCalculatorRegex
    {
    private:
        OperandType  m_result;
        OperatorType m_nextOperator;
        std::string  m_regex;
        std::regex   m_tokens_regex;

    public:
        // c'tors
        ChainCalculatorRegex();

        // getter
        auto getResult() const { return m_result; }

        // public interface
        void calc(const std::string& expression);

    private:
        // private helper method
        Token<OperandType> getNextToken(std::sregex_iterator iter);
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
