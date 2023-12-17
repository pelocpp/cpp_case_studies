// =====================================================================================
// ChainCalculatorConstexpr.cpp
// =====================================================================================

#include "ChainCalculatorConstexpr.h"

namespace ChainArithmetic_Constexpr {

    // c'tor(s)
    constexpr Token::Token()
        : m_type{ TokenType::Null },
        m_op{ OperatorType::NullOp },
        m_value{ OperandType{} }
    {}

    constexpr Token::Token(OperatorType op)
        : m_type{ TokenType::Operator },
        m_op{ op }, 
        m_value{ OperandType{} }
    {}

    constexpr Token::Token(OperandType value)
        : m_type{ TokenType::Operand },
        m_op{ OperatorType::NullOp },
        m_value{ value }
    {}

    // getter
    constexpr TokenType Token::getTokenType() const { return m_type; }
    constexpr OperatorType Token::getOperatorType() const { return m_op; }
    constexpr OperandType Token::getValue() const { return m_value; }

    // public interface
    constexpr OperandType ChainCalculatorConstexpr::calc(const char* expression)
    {
        // reset calculator
        OperandType result{};
        OperatorType nextOperator{ OperatorType::NullOp };

        // setup scanner
        const char* pos = expression;

        // need state variable to control correct syntax of chain expression
        auto m_expectedOperator{ false };

        while (*pos != '\0') {

            Token tok{ getNextToken(&pos) };

            if (tok.getTokenType() == TokenType::Operator)
            {
                if (m_expectedOperator == false) {
                    throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
                }

                // store next operator
                nextOperator = tok.getOperatorType();

                // toggle parsing state
                m_expectedOperator = !m_expectedOperator;
            }
            else if (tok.getTokenType() == TokenType::Operand)
            {
                if (m_expectedOperator == true) {
                    throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operand");
                }

                OperandType value{ tok.getValue() };

                switch (nextOperator)
                {
                case OperatorType::NullOp:
                    result = value;
                    break;
                case OperatorType::AddOp:
                    result = result + value;
                    break;
                case OperatorType::SubOp:
                    result = result - value;
                    break;
                case OperatorType::MulOp:
                    result = result * value;
                    break;
                case OperatorType::DivOp:
                    result = result / value;
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

        return result;
    }

    constexpr bool ChainCalculatorConstexpr::isDigit(const char ch) {

        return (ch >= '0' && ch <= '9') ? true : false;
    }

    constexpr Token ChainCalculatorConstexpr::getNextToken(const char** pos)
    {
        Token tok{};

        // skip blanks, if any ...
        char ch{ **pos };
        if (ch == ' ') {

            ++*pos;
            while (**pos != '\0' && **pos == ' ') {
                ++*pos;
            }

            if (**pos != '\0') {
                return tok;
            }
        }

        switch (ch)
        {
        case '+':
            tok = Token{ OperatorType::AddOp };
            ++*pos;
            break;

        case '-':
            tok = Token{ OperatorType::SubOp };
            ++*pos;
            break;

        case '*':
            tok = Token{ OperatorType::MulOp };
            ++*pos;
            break;

        case '/':
            tok = Token{ OperatorType::DivOp };
            ++*pos;
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
            while (**pos != '\0' && isDigit(**pos))
            {
                value = 10 * value + (**pos - '0');
                ++*pos;
            }

            tok = Token{ value };
            break;
        }

        default:
            break;
        }

        return tok;
    }
}

void test_chain_arithmetic_20()
{
    using namespace ChainArithmetic_Constexpr;

    constexpr Token tok1{ OperatorType::AddOp };
    constexpr Token tok2{ 123 };

    constexpr ChainCalculatorConstexpr chain;

    constexpr OperandType result1 = ChainCalculatorConstexpr::calc(
        "10 + 20 + 30"
    );
    static_assert(result1 == 60);

    constexpr OperandType result2 = ChainCalculatorConstexpr::calc(
        "1 + 3 * 5 - 2 * 2 - 8 / 2"
    );
    static_assert(result2 == 14);

    constexpr OperandType result3 = ChainCalculatorConstexpr::calc(
        "10 + 20 -  5 * 3 / 5"
    );
    static_assert(result3 == 15);

    constexpr OperandType result4 = ChainCalculatorConstexpr::calc(
        "10 - 5 * 3 + 35 / 10"
    );
    static_assert(result4 == 5);

    constexpr OperandType result5 = ChainCalculatorConstexpr::calc(
        "2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 - 1"
    );
    static_assert(result5 == 1023);
}

// =====================================================================================
// End-of-File
// =====================================================================================
