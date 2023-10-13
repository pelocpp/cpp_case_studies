// =====================================================================================
// ChainCalculatorRegex.cpp
// =====================================================================================

#include "ChainCalculatorRegex.h"

namespace ChainArithmetic_Regex {

    // c'tors
    ChainCalculatorRegex::ChainCalculatorRegex() :
        m_result{},
        m_nextOperator{ OperatorType::NullOp },
        m_regex{ "([1-9][0-9]*)|\\+|\\-|\\*|\\/" },
        m_tokens_regex{ m_regex }
    {}

    // public interface
    void ChainCalculatorRegex::calc(std::string expression)
    {
        // reset calculator
        m_result = 0;
        m_nextOperator = OperatorType::NullOp;

        // setup scanner
        auto begin{
            std::sregex_iterator {
                expression.begin(),
                expression.end(),
                m_tokens_regex
            }
        };
        auto end{ std::sregex_iterator{} };

        // need state variable to control correct syntax of chain expression
        bool m_expectedOperator{ false };

        while (begin != end) {

            Token<OperandType> tok{ getNextToken(begin) };

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

            ++begin;
        }

        // last argument should be a operand
        if (m_expectedOperator == false) {
            throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
        }
    }

    // private helper method
    Token<OperandType> ChainCalculatorRegex::getNextToken(std::sregex_iterator iter)
    {
        std::smatch match{ *iter };

        std::string s{ match.str() };

        Token<OperandType> tok{};

        switch (s[0])
        {
        case '+':
            tok = Token<OperandType>{ OperatorType::AddOp };
            // std::cout << '+' << std::endl;
            break;

        case '-':
            tok = Token<OperandType>{ OperatorType::SubOp };
            // std::cout << '-' << std::endl;
            break;

        case '*':
            tok = Token<OperandType>{ OperatorType::MulOp };
            // std::cout << '*' << std::endl;
            break;

        case '/':
            tok = Token<OperandType>{ OperatorType::DivOp };
            // std::cout << '/' << std::endl;
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
            OperandType value{ stoll(s) };
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
