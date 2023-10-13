#include "ChainCalculatorModern.h"

namespace ChainArithmetic_Modern {

    // c'tors
    ChainCalculatorModern::ChainCalculatorModern() :
        m_result{},
        m_nextOperator{ '?' },
        m_expectedOperator{ false }
    {}

    // public interface
    void ChainCalculatorModern::calc(auto ... args)
    {
        static_assert(sizeof ... (args) > 0);

        // reset calculator
        m_result = 0;
        m_nextOperator = '?';

        // initialize parsing state
        m_expectedOperator = false;

        (calc(args), ...);

        // last argument should be a operand
        if (m_expectedOperator == false) {
            throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
        }
    }

    void ChainCalculatorModern::calc(auto arg)
    {
        //  std::cout << arg << std::endl;

        using Type = decltype (arg);

        if constexpr (std::is_same<Type, char>::value == true)
        {
            // check parsing state
            if (m_expectedOperator == false) {
                throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
            }

            //  std::cout << "Operator: " << arg << std::endl;

                // store next operator
            m_nextOperator = arg;

            // toggle parsing state
            m_expectedOperator = !m_expectedOperator;
        }
        // hmmm, da sollte man die char Typen wegnehmen ..................
        else if constexpr (std::is_integral<Type>::value == true)
        {
            // check parsing state
            if (m_expectedOperator == true) {
                throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operand");
            }

            //  std::cout << "Argument: " << arg << std::endl;

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
}