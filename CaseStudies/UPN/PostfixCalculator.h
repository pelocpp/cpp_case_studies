// =====================================================================================
// PostfixCalculator.h
// =====================================================================================

#pragma once

template <typename T>
class PostfixCalculator
{
private:
    std::stack<Token<T>> m_stack;  // temporary stack of operands

public:
    // public interface
    template <typename Iter>
    T calc(Iter begin, Iter end)
    {
        std::stack<Token<T>> m_stack;  // temporary stack of operands

        for (Iter it{ begin }; it != end; ++it)
        {
            Token<T> tok{ *it };

            if (tok.getTokenType() == TokenType::Operand)
            {
                // push operand on temporary operand stack
                m_stack.push(tok);
            }
            else if (tok.getTokenType() == TokenType::Operator)
            {
                // binary operator, retrieve operands from operand stack
                Token<T> right{ m_stack.top() };
                m_stack.pop();

                Token<T> left{ m_stack.top() };
                m_stack.pop();

                T rightValue{ right.getValue() };
                T leftValue{ left.getValue() };
                T result{};

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
                default:
                    break;
                }

                // push result to operand stack
                Token<T> val{ TokenType::Operand, result };
                m_stack.push(val);
            }
        }

        // retrieve result from stack
        Token<T> result{ m_stack.top() };
        m_stack.pop();
        return result.getValue();
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
