// =====================================================================================
// ChainCalculatorClassic.h
// =====================================================================================

#pragma once

#include "Token.h"

namespace ChainArithmetic_Classic {

    class ChainCalculatorClassic
    {
    private:
        OperandType  m_result;
        OperatorType m_nextOperator;
        std::string::const_iterator m_begin;
        std::string::const_iterator m_end;

    public:
        // c'tors
        ChainCalculatorClassic();

        // getter
        auto getResult() const { return m_result; }

        // public interface
        void calc(const std::string& expression);

    private:
        // private helper method
        Token<OperandType> getNextToken();
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
