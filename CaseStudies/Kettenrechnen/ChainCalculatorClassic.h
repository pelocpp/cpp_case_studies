// =====================================================================================
// ChainCalculatorClassic.h
// =====================================================================================

#pragma once

#include "ChainArithmetic.h"
#include "Token.h"

namespace ChainArithmetic_Classic {

    class ChainCalculatorClassic
    {
    private:
        OperandType  m_result;
        OperatorType m_nextOperator;
        std::string::iterator m_begin;
        std::string::iterator m_end;

    public:
        // c'tors
        ChainCalculatorClassic();

        // getter
        auto getResult() { return m_result; }

        // public interface
        void calc(std::string expression);

    private:
        // private helper method
        Token<OperandType> getNextToken();
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
