// =====================================================================================
// ChainExpressionGenerator.cpp
// =====================================================================================

#include "ChainExpressionGenerator.h"

namespace ChainArithmetic_ExpressionGenerator {

    std::string ChainExpressionGenerator::createExpression(int numOperations)
    {
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
}

// =====================================================================================
// End-of-File
// =====================================================================================
