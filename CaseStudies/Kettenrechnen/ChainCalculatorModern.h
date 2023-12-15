// =====================================================================================
// ChainCalculatorModern.h
// =====================================================================================

#pragma once

#include <iostream>
#include <type_traits>
#include <concepts>

#include "Token.h"

namespace ChainArithmetic_Modern {

    class ChainCalculatorModern
    {
    private:
        OperandType m_result;
        char m_nextOperator;
        bool m_expectedOperator;

    public:
        // c'tors
        ChainCalculatorModern () :
            m_result{},
            m_nextOperator{ '?' },
            m_expectedOperator{ false }
        {}

        // getter
        auto getResult() const { return m_result; }

    public:
        void calc(std::integral auto ... args)
        {
            static_assert(sizeof ... (args) > 0);

            // reset calculator
            m_result = 0;
            m_nextOperator = '?';

            // initialize parsing state
            m_expectedOperator = false;

            ( calc(args) , ... );

            // last argument should be a operand
            if (m_expectedOperator == false) {
                throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
            }
        }

    private:
        // private helper method
        void calc(std::integral auto arg)
        {
            using Type = decltype(arg);

            if constexpr (std::is_same<Type, char>::value == true)
            {
                // check parsing state
                if (m_expectedOperator == false) {
                    throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
                }

                // store next operator
                m_nextOperator = arg;

                // toggle parsing state
                m_expectedOperator = !m_expectedOperator;
            }

            if constexpr (std::is_integral<Type>::value == true && !std::same_as<Type, char>)
            {
                // check parsing state
                if (m_expectedOperator == true) {
                    throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operand");
                }

                switch (m_nextOperator)
                {
                case '?':
                    m_result = arg;
                    break;
                case '+':
                    m_result = m_result + arg;
                    break;
                case '-':
                    m_result = m_result - arg;
                    break;
                case '*':
                    m_result = m_result * arg;
                    break;
                case '/':
                    m_result = m_result / arg;
                    break;
                }

                // toggle parsing state
                m_expectedOperator = !m_expectedOperator;
            }
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
