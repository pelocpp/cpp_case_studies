// =====================================================================================
// UPN.cpp
// =====================================================================================

#include <iostream>
#include <list>
#include <stack>
#include <string>

#include "Token.h"
#include "Scanner.h"
#include "PostfixCalculator.h"

int PostfixCalculator::calc(std::list<Token> postfix)
{
    std::stack<Token> m_stack;  // temporary stack of operands

   // std::list<Token>::iterator it;

    // for (it = postfix.cbegin(); it != postfix.cend(); it++)
    for (const Token& tok : postfix)
    {
       // Token tok = *it;

        if (tok.getTokenType() == TokenType::Operand)
        {
            // push operand on temporary operand stack
            m_stack.push(tok);
        }
        else if (tok.getTokenType() == TokenType::Operator)
        {
            // binary operator, retrieve operands from operand stack
            Token right{ m_stack.top() };
            m_stack.pop();

            Token left{ m_stack.top() };
            m_stack.pop();

            int rightValue{ right.getValue() };
            int leftValue{ left.getValue() };
            int result{};

            OperatorType op{ tok.getOperatorType() };
            switch (op)
            {
            case OperatorType::AddOp:
                result = leftValue + rightValue;
                break;
            case OperatorType::SubOp:
                result = leftValue - rightValue;
                break;
            case OperatorType::MulOp:
                result = leftValue * rightValue;
                break;
            case OperatorType::DivOp:
                result = leftValue / rightValue;
                break;
            case OperatorType::ModOp:
                result = leftValue % rightValue;
                break;
            }

            // push result to operand stack
            Token val(TokenType::Operand, result);
            m_stack.push(val);
        }
    }

    // retrieve result from stack
    Token result{ m_stack.top() };
    m_stack.pop();
    return result.getValue();
}

// =====================================================================================
// End-of-File
// =====================================================================================
