#include "ChainCalculatorSTL.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <numeric>
#include <variant>

namespace ChainArithmetic_STL {

    ChainCalculatorSTL::ChainCalculatorSTL() :
        m_result{},
        m_nextOperator{ OperatorType::NullOp }
    {}

    // public interface
    void ChainCalculatorSTL::calc(auto ... args)
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