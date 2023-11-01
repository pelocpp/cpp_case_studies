// =====================================================================================
// Program.cpp // Kettenrechnen
// =====================================================================================

#include <iostream>
#include <numeric>
#include <variant>
#include <vector>
#include <concepts>

#include "Token.h"

namespace ChainArithmetic_STL {

    class ChainCalculatorSTL
    {
    private:
        OperandType  m_result;
        OperatorType m_nextOperator;

    public:
        // c'tors
        ChainCalculatorSTL() :
            m_result{},
            m_nextOperator{ OperatorType::NullOp }
        {}

        // getter
        auto getResult() { return m_result; }

        // public interface
        void calc(std::integral auto ... args)
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
                [&](OperandType element, const auto& next) mutable
                {
                    OperandType result{ element };

                    std::visit(

                        [&](const auto& value) {

                            using ElemType = decltype (value);

                            using ElemTypeWithoutReference =
                                typename std::remove_reference<ElemType>::type;

                            using ElemTypeWithoutReferenceAndConst =
                                typename std::remove_const<ElemTypeWithoutReference>::type;

                            if constexpr (std::is_same<ElemTypeWithoutReferenceAndConst, char>::value == true)
                            {
                                // store next operator
                                switch (value)
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
                                    result = value;
                                    break;
                                case OperatorType::AddOp:
                                    result = element + value;
                                    break;
                                case OperatorType::SubOp:
                                    result = element - value;
                                    break;
                                case OperatorType::MulOp:
                                    result = element * value;
                                    break;
                                case OperatorType::DivOp:
                                    result = element / value;
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
}

// =====================================================================================
// End-of-File
// =====================================================================================
