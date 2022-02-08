// =====================================================================================
// InfixToPostfixConverter.h
// =====================================================================================

#pragma once

template <typename T>
class InfixToPostfixConverter
{
private:
    std::list<Token<T>> m_postfix;     // postfix expression (output)
    std::stack<Token<T>> m_stack;      // temporary stack of operators and brackets

public:
    // public interface
    template <typename Iter>
    std::list<Token<T>> convert(Iter begin, Iter end) {
        clear();

        Token<T> next{};
        if (begin != end) {
            next = *begin;
            ++begin;
        }

        while (next.getTokenType() != TokenType::Null)
        {
            if (next.getTokenType() == TokenType::Operand)
                processOperand(next);
            else if (next.getTokenType() == TokenType::Operator)
                processOperator(next);
            else if (next.getTokenType() == TokenType::LBracket)
                processLeftParenthesis(next);
            else if (next.getTokenType() == TokenType::RBracket)
                processRightParenthesis();

            dumpStacks(next);

            if (begin != end) {
                next = *begin;
                ++begin;
            }
            else {
                next = {};
            }
        }

        processEndOfInput();
        dumpStacks(next);

        return m_postfix;
    }

private:
    // helper methods
    void clear() {
        m_postfix.clear();
    }

    void processOperand(Token<T> next) {
        // append operand to the postfix buffer
        m_postfix.push_back(next);
    }

    void processOperator(Token<T> next) {
        /**
         * Move operators from the stack to the output buffer, as long as
         * - the incoming operator precedence is lower or equal to a stacked operator,
         * - no left parenthesis appears on the stack
         * - and the stack is not empty.
         * The incoming operator is stacked.
         */
        do
        {
            if (m_stack.empty())
                break;

            // left parenthesis on stack encountered
            Token<T> top = m_stack.top();
            if (top.getTokenType() == TokenType::LBracket)
                break;

            if (next.getPrecedence() <= top.getPrecedence())
            {
                m_stack.pop();
                m_postfix.push_back(top);
            }
            else {
                break;
            }
        } while (true);

        // stack incoming operator
        m_stack.push(next);
    }

    void processLeftParenthesis(Token<T> next) {
        // push a left parenthesis onto the operator stack
        m_stack.push(next);
    }

    void processRightParenthesis()
    {
        // move operators from the stack to the output buffer, until a left 
        // parenthesis appears on the stack (the left parenthesis is discarded)
        do
        {
            Token<T> top = m_stack.top();

            if (top.getTokenType() == TokenType::LBracket)
                break;

            m_stack.pop();
            m_postfix.push_back(top);
        } while (true);

        // discard left parenthesis
        m_stack.pop();
    }

    void processEndOfInput() {
        // copy remaining elements from operator stack to postfix buffer
        while (!m_stack.empty())
        {
            Token<T> top = m_stack.top();
            m_stack.pop();
            m_postfix.push_back(top);
        }
    }

    void dumpStacks(Token<T> next) {
        // dump latest token
        std::cout << next << "  ";

        // output stack (not trivial, because stack has limited iterator support)
        std::cout << "[";
        if (m_stack.size() != 0) {
            // need a copy of the stack
            std::stack<Token<T>> stack{ m_stack };
            std::vector<Token<T>> tmp{};
            while (!stack.empty()) {
                Token<T> top = stack.top();
                stack.pop();
                tmp.push_back(top);
            }

            std::reverse(
                std::begin(tmp),
                std::end(tmp)
            );

            std::for_each(
                std::begin(tmp),
                std::prev(std::end(tmp)),
                [](const Token<T>& token) {
                    std::cout << token << ", ";
                }
            );

            const Token<T>& latest = tmp.back();
            std::cout << latest;
        }
        std::cout << "]";

        // fill gap equally spaced
        const size_t MaxDistance = 20;
        size_t size = m_stack.size();
        size_t count{};

        if (size == 0) {
            count = MaxDistance - 2;
        }
        else if (size == 1) {
            count = MaxDistance - 3;
        }
        else {
            count = MaxDistance - (3 * size);
        }

        for (size_t n{}; n != count; ++n) {
            std::cout << " ";
        }

        // output so far calculated tokens in postfix order
        std::cout << '[';
        if (m_postfix.size() != 0) {

            std::for_each(
                std::begin(m_postfix),
                std::prev(std::end(m_postfix)),
                [](const Token<T>& token) {
                    std::cout << token << ", ";
                }
            );

            const Token<T>& latest = m_postfix.back();
            std::cout << latest;
        }

        std::cout << ']';
        std::cout << std::endl;
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
