// =====================================================================================
// Token.h
// =====================================================================================

// chain arithmetic

// to be done: Zeitvergleich

// TBD: große Kettenrechnungen generieren ...

// TBD:  geht da was mit std::accumulate

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <list>
#include <numeric>
#include <type_traits>
#include <stdexcept>
#include <regex>
#include <random>
#include <variant>
#include <chrono>

#include "ChainArithmetic.h"
#include "Token.h"


#include "ChainCalculatorSTL.h"

namespace ChainArithmetic_STL {


        ChainCalculator::ChainCalculator() :
            m_result{},
            m_nextOperator{ OperatorType::NullOp }
        {}

        // getter
        auto ChainCalculator::getResult() { return m_result; }

        // public interface
        void ChainCalculator::calc(auto ... args)
        {
            static_assert(sizeof ... (args) > 0);

            // reset calculator
            m_result = 0;
            m_nextOperator = OperatorType::NullOp;

            // unpack paramerters
            std::vector<std::variant<char, OperandType>> expression{ args ... };

            // need state variable to control correct syntax of chain expression
            bool expectedOperator{ false };

            OperatorType nextOperator{};

            m_result = std::accumulate(
                std::begin(expression),
                std::end(expression),
                static_cast<OperandType>(0), // first element
                [&](OperandType first, const auto& next) mutable
                {
                    OperandType result{ first };

                    std::visit(
                        [&](const auto& element)
                        {
                            using ElemType = decltype (element);

                            using ElemTypeWithoutReference =
                                typename std::remove_reference<ElemType>::type;

                            using ElemTypeWithoutReferenceAndConst =
                                typename std::remove_const<ElemTypeWithoutReference>::type;

                            if constexpr (std::is_same<ElemTypeWithoutReferenceAndConst, char>::value == true)
                            {
                                // store next operator
                                switch (element)
                                {
                                case '+':
                                    nextOperator = OperatorType::AddOp;
                                    break;

                                case '-':
                                    nextOperator = OperatorType::SubOp;
                                    break;

                                case '*':
                                    nextOperator = OperatorType::MulOp;
                                    break;

                                case '/':
                                    nextOperator = OperatorType::DivOp;
                                    break;
                                }

                                // toggle parsing state
                                expectedOperator = !expectedOperator;
                            }

                            if constexpr (std::is_same<ElemTypeWithoutReferenceAndConst, OperandType>::value == true)
                            {
                                // check parsing state
                                if (expectedOperator == true) {
                                    throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operand");
                                }

                                switch (nextOperator)
                                {
                                case OperatorType::NullOp:
                                    result = element;
                                    break;
                                case OperatorType::AddOp:
                                    result = first + element;
                                    break;
                                case OperatorType::SubOp:
                                    result = first - element;
                                    break;
                                case OperatorType::MulOp:
                                    result = first * element;
                                    break;
                                case OperatorType::DivOp:
                                    result = first / element;
                                    break;
                                }

                                // toggle parsing state
                                expectedOperator = !expectedOperator;
                            }
                        },
                        next
                    );

                    return result;
                }
            );

            // last argument should be a operand
            if (expectedOperator == false) {
                throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
            }
        }
    };

    //class ChainCalculator
    //{
    //private:
    //    OperandType  m_result;          // long long: Hmmm, geht das irgendwie anders  // evtl.  std::commmon_type
    //    OperatorType m_nextOperator;

    //public:
    //    // c'tors
    //    ChainCalculator() :
    //        m_result{},
    //        m_nextOperator{ OperatorType::NullOp }
    //    {}

    //    // getter
    //    auto getResult() { return m_result; }

    //    // public interface
    //    void calc(auto ... args)
    //    {
    //        static_assert(sizeof ... (args) > 0);

    //        // reset calculator
    //        m_result = 0;
    //        m_nextOperator = OperatorType::NullOp;

    //        // unpack paramerters
    //        std::vector<std::variant<char, OperandType>> expression{ args ... };

    //        // need state variable to control correct syntax of chain expression
    //        bool expectedOperator{ false };

    //        OperatorType nextOperator{};

    //        m_result = std::accumulate(
    //            std::begin(expression),
    //            std::end(expression),
    //            static_cast<OperandType>(0), // first element
    //            [&](OperandType first, const auto& next) mutable
    //            {
    //                OperandType result{ first };

    //                std::visit(
    //                    [&](const auto& element) 
    //                    {
    //                        using ElemType = decltype (element);

    //                        using ElemTypeWithoutReference =
    //                            typename std::remove_reference<ElemType>::type;

    //                        using ElemTypeWithoutReferenceAndConst =
    //                            typename std::remove_const<ElemTypeWithoutReference>::type;

    //                        if constexpr (std::is_same<ElemTypeWithoutReferenceAndConst, char>::value == true)
    //                        {
    //                            // store next operator
    //                            switch (element)
    //                            {
    //                            case '+':
    //                                nextOperator = OperatorType::AddOp;
    //                                break;

    //                            case '-':
    //                                nextOperator = OperatorType::SubOp;
    //                                break;

    //                            case '*':
    //                                nextOperator = OperatorType::MulOp;
    //                                break;

    //                            case '/':
    //                                nextOperator = OperatorType::DivOp;
    //                                break;
    //                            }

    //                            // toggle parsing state
    //                            expectedOperator = !expectedOperator;
    //                        }

    //                        if constexpr (std::is_same<ElemTypeWithoutReferenceAndConst, OperandType>::value == true)
    //                        {
    //                            // check parsing state
    //                            if (expectedOperator == true) {
    //                                throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operand");
    //                            }

    //                            switch (nextOperator)
    //                            {
    //                            case OperatorType::NullOp:
    //                                result = element;
    //                                break;
    //                            case OperatorType::AddOp:
    //                                result = first + element;
    //                                break;
    //                            case OperatorType::SubOp:
    //                                result = first - element;
    //                                break;
    //                            case OperatorType::MulOp:
    //                                result = first * element;
    //                                break;
    //                            case OperatorType::DivOp:
    //                                result = first / element;
    //                                break;
    //                            }

    //                            // toggle parsing state
    //                            expectedOperator = !expectedOperator;
    //                        }
    //                    },
    //                    next
    //                );

    //                return result;
    //            }
    //        );

    //        // last argument should be a operand
    //        if (expectedOperator == false) {
    //            throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
    //        }
    //    }
    //};
//}

namespace ChainArithmetic_ExpressionGenerator {

    class ChainArithmeticHelper
    {
    public:
        static std::string createExpression(int numOperations) {

            std::random_device device{};

            std::uniform_int_distribution<int> distOperator(0, 3);
            std::uniform_int_distribution<int> distOperand(1, 99);

            std::string expression{};

            // creating first random operand
            int operand{ distOperand(device) };
            expression.append(std::to_string(operand));

            for (int i{}; i != numOperations; ++i) {

                // creating random operator
                int op{ distOperator(device) };

                switch (op)
                {
                case 0:
                    expression.append(std::string{ " + " });
                    break;
                case 1:
                    expression.append(std::string{ " - " });
                    break;
                case 2:
                    expression.append(std::string{ " * " });
                    break;
                case 3:
                    expression.append(std::string{ " / " });
                    break;
                default:
                    expression.append(std::string{ " <error> " });
                    break;
                }

                // creating next random operand
                operand = distOperand(device);
                expression.append(std::to_string(operand));
            }

            return expression;
        }
    };
}

namespace ChainArithmetic_Classic {

    class ChainCalculator
    {
    private:
        OperandType  m_result;          // long long: Hmmm, geht das irgendwie anders  // evtl.  std::commmon_type
        OperatorType m_nextOperator;
        std::string::iterator m_begin;
        std::string::iterator m_end;

    public:
        // c'tors
        ChainCalculator() :
            m_result{},
            m_nextOperator{ OperatorType::NullOp },
            m_begin{},
            m_end{}
        {}

        // getter
        auto getResult() { return m_result; }

        // public interface
        void calc(std::string expression)
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

    private:
        Token<OperandType> getNextToken()
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
    };
}

namespace ChainArithmetic_Regex {

    class ChainCalculator
    {
    private:
        OperandType  m_result;          // long long: Hmmm, geht das irgendwie anders  // evtl.  std::commmon_type
        OperatorType m_nextOperator;
        std::string  m_regex;
        std::regex   m_tokens_regex;

    public:
        // c'tors
        ChainCalculator() :
            m_result{},
            m_nextOperator{ OperatorType::NullOp }, 
            m_regex{ "([1-9][0-9]*)|\\+|\\-|\\*|\\/" }, 
            m_tokens_regex{ m_regex }
        {}

        // getter
        auto getResult() { return m_result; }

        // public interface
        void calc(std::string expression)
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

    private:

        Token<OperandType> getNextToken(std::sregex_iterator iter)
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
    };
}

namespace ChainArithmetic_Modern {

    class ChainCalculator
    {
    private:
        long long m_result;     // long long: Hmmm, geht das irgendwie anders  // evtl.  std::commmon_type
        char m_nextOperator;
        bool m_expectedOperator;

    public:
        // c'tors
        ChainCalculator() :
            m_result{}, 
            m_nextOperator{ '?' },
            m_expectedOperator{ false }
        {}

        // getter
        auto getResult() { return m_result; }

    public:
        void calc(auto ... args)
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

        // geht hier auch
        // calc(concept auto arg)   , also das ganze mit einem führenden concept ?????? 

        void calc(auto arg)
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
    };
}

//// =====================================================================================
//
//void test_chain_arithmetic()
//{
//    //test_chain_arithmetic_00();
//    //test_chain_arithmetic_01();
//    //test_chain_arithmetic_02();
//    //test_chain_arithmetic_03();
//    //test_chain_arithmetic_04();
//    //test_chain_arithmetic_05();
//    //test_chain_arithmetic_06();
//    //test_chain_arithmetic_07();
//    test_chain_arithmetic_10();
//}

// =====================================================================================
// End-of-File
// =====================================================================================