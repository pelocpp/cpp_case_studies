// =====================================================================================
// ChainCalculatorClassic.cpp
// =====================================================================================

#include "ChainCalculatorClassic.h"

namespace ChainArithmetic_Classic {

    // c'tors
    ChainCalculatorClassic::ChainCalculatorClassic() :
        m_result{},
        m_nextOperator{ OperatorType::NullOp },
        m_begin{},
        m_end{}
    {}

    // public interface
    void ChainCalculatorClassic::calc(std::string expression)
    {
        // reset calculator
        m_result = 0;
        m_nextOperator = OperatorType::NullOp;

        // setup scanner
        m_begin = expression.begin();
        m_end = expression.end();

        // need state variable to control correct syntax of chain expression
        bool m_expectedOperator{ false };

        while (m_begin != m_end) {

            Token<OperandType> tok{ getNextToken() };

            if (tok.getTokenType() == TokenType::Operator)
            {
                if (m_expectedOperator == false) {
                    throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
                }

                // store next operator
                m_nextOperator = tok.getOperatorType();

                // toggle parsing state
                m_expectedOperator = !m_expectedOperator;
            }
            else if (tok.getTokenType() == TokenType::Operand)
            {
                if (m_expectedOperator == true) {
                    throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operand");
                }

                OperandType value{ tok.getValue() };

                switch (m_nextOperator)
                {
                case OperatorType::NullOp:
                    m_result = value;
                    break;
                case OperatorType::AddOp:
                    m_result = m_result + value;
                    break;
                case OperatorType::SubOp:
                    m_result = m_result - value;
                    break;
                case OperatorType::MulOp:
                    m_result = m_result * value;
                    break;
                case OperatorType::DivOp:
                    m_result = m_result / value;
                    break;
                }

                // toggle parsing state
                m_expectedOperator = !m_expectedOperator;
            }
        }

        // last argument should be a operand
        if (m_expectedOperator == false) {
            throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
        }
    }

    Token<OperandType> ChainCalculatorClassic::getNextToken()
    {
        char ch{ *m_begin };
        Token<OperandType> tok{};

        // sip blanks, if any ...
        if (ch == ' ') {

            ++m_begin;
            while (m_begin != m_end && *m_begin == ' ') {
                ++m_begin;
            }

            if (m_begin == m_end) {
                return tok;
            }
        }

        switch (ch)
        {
        case '+':
            tok = Token<OperandType>{ OperatorType::AddOp };
            ++m_begin;
            break;

        case '-':
            tok = Token<OperandType>{ OperatorType::SubOp };
            ++m_begin;
            break;

        case '*':
            tok = Token<OperandType>{ OperatorType::MulOp };
            ++m_begin;
            break;

        case '/':
            tok = Token<OperandType>{ OperatorType::DivOp };
            ++m_begin;
            break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            OperandType value{};
            while (m_begin != m_end && std::isdigit(*m_begin))
            {
                value = 10 * value + (*m_begin - '0');
                ++m_begin;
            }

            tok = Token<OperandType>{ value };
            break;
        }

        default:
            break;
        }

        return tok;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
