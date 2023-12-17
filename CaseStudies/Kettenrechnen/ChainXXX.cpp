// =====================================================================================
// ChainCalculator_Constexpr.cpp
// =====================================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

namespace ChainArithmetic_XXX {

    enum class TokenType { Null, Operator, Operand };

    enum class OperatorType { NullOp, AddOp, SubOp, MulOp, DivOp };

    using OperandType = signed long long;

    class Token
    {
    private:
        // member data
        TokenType     m_type;     // classification of token
        OperatorType  m_op;       // classification of operator (TokenType == Operator)
        OperandType   m_value;    // value of constant (TokenType == Operand)

    public:
        // c'tor(s)
        constexpr Token()
            : m_type{ TokenType::Null }, m_op{ OperatorType::NullOp }, m_value{ OperandType{} }
        {}

        constexpr Token(OperatorType op)
            : m_type{ TokenType::Operator }, m_op{ op }, m_value{ OperandType{} }
        {}

        constexpr Token(OperandType value)
            : m_type{ TokenType::Operand }, m_op{ OperatorType::NullOp }, m_value{ value }
        {}

        // getter
        constexpr TokenType getTokenType() const { return m_type; }
        constexpr OperatorType getOperatorType() const { return m_op; }
        constexpr OperandType getValue() const { return m_value; }
    };

    class ChainCalculatorConstexpr
    {
    private:
       //mutable OperandType  m_result;
       // mutable OperatorType m_nextOperator;
        //mutable std::string::const_iterator m_begin;
        //mutable std::string::const_iterator m_end;

        // mutable const char* m_pos;

    public:
        // c'tors
        constexpr ChainCalculatorConstexpr();

        // public interface
        constexpr OperandType calc(const char* expression) const;

    private:
        // private helper methods
        constexpr bool isDigit(const char) const;
        constexpr Token getNextToken(const char** ) const;
    };

    // c'tors
    constexpr ChainCalculatorConstexpr::ChainCalculatorConstexpr() 
        // m_nextOperator{ OperatorType::NullOp },
    //m_begin{},
    //m_end{}
    {}

    // public interface
    constexpr OperandType ChainCalculatorConstexpr::calc(const char* expression) const
    {
        // reset calculator
        OperandType result{};
        OperatorType nextOperator{ OperatorType::NullOp };

        const char* pos;

        result = 0;
        nextOperator = OperatorType::NullOp;

        // setup scanner
        pos = expression;
        //m_begin = expression.begin();
        //m_end = expression.end();

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

    constexpr bool ChainCalculatorConstexpr::isDigit(const char ch) const {

        return (ch >= '0' && ch <= '9') ? true : false;
    }

    constexpr Token ChainCalculatorConstexpr::getNextToken(const char** pos) const
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

void test_chain_arithmetic_XX()
{
    using namespace ChainArithmetic_XXX;

    constexpr Token tok1{ OperatorType::AddOp };
    constexpr Token tok2{ 123 };


    constexpr ChainCalculatorConstexpr chain;

    chain.calc("10 + 20 + 30");
    
    constexpr OperandType result = chain.calc("1 + 3 * 5 - 2 * 2 - 8 / 2");
  //  constexpr OperandType result = chain.calc("1 + 30");

    std::cout << "Result: " << result << std::endl;

    //chain.calc("1 + 3 * 5 - 2 * 2 - 8 / 2");
    //result = chain.getResult();
    //std::cout << "Result: " << result << std::endl;

    //chain.calc("10 + 20 -  5 * 3 / 5");  // 10 + 20 - 5 * 3 / 5 == 15
    //result = chain.getResult();
    //std::cout << "Result: " << result << std::endl;

    //chain.calc("10 - 5 * 3 + 35 / 10");   //   10 - 5 * 3 + 35 / 10 == 5
    //result = chain.getResult();
    //std::cout << "Result: " << result << std::endl;
}


// =====================================================================================
// End-of-File
// =====================================================================================
