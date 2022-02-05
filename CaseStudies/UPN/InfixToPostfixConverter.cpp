// =====================================================================================
// InfixToPostfixConverter.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>

#include "Token.h"
#include "InfixToPostfixConverter.h"
//
//std::list<Token> InfixToPostfixConverter::convert(const std::list<Token>& infix)
//{
//    clear();
//
//    m_infix = infix;  // want a copy of the input parameter
//
//    while ((m_next = nextToken()).getTokenType() != TokenType::Null)
//    {
//        if (m_next.getTokenType() == TokenType::Operand)
//            processOperand();
//        else if (m_next.getTokenType() == TokenType::Operator)
//            processOperator();
//        else if (m_next.getTokenType() == TokenType::LBracket)
//            processLeftParenthesis();
//        else if (m_next.getTokenType() == TokenType::RBracket)
//            processRightParenthesis();
//
//        dumpStacks();
//    }
//
//    processEndOfInput();
//    dumpStacks();
//
//    return m_postfix;
//}
//
//// helper methods
//void InfixToPostfixConverter::clear()
//{
//    m_postfix.clear();
//    m_it = m_infix.begin();
//}
//
//Token InfixToPostfixConverter::nextToken()
//{
//    Token next{};
//    if (m_it != m_infix.end())
//    {
//        next = *m_it;
//        ++m_it;
//    }
//
//    return next;
//}
//
//void InfixToPostfixConverter::processOperand()
//{
//    // append operand to the postfix buffer
//    m_postfix.push_back(m_next);
//}
//
//void InfixToPostfixConverter::processOperator()
//{
//    /**
//     * Move operators from the stack to the output buffer,
//     * as long as
//     * - the incoming operator precedence is lower or equal to a stacked operator,
//     * - no left parenthesis appears on the stack
//     * - and the stack is not empty.
//     * The incomming operator is stacked.
//     */
//    do
//    {
//        if (m_stack.empty())
//            break;
//
//        // left parenthesis on stack encountered
//        Token top = m_stack.top();
//        if (top.getTokenType() == TokenType::LBracket)
//            break;
//
//        if (m_next.getPrecedence() <= top.getPrecedence())
//        {
//            m_stack.pop();
//            m_postfix.push_back(top);
//        }
//        else {
//            break;
//        }
//    } 
//    while (true);
//
//    // stack incoming operator
//    m_stack.push(m_next);
//}
//
//void InfixToPostfixConverter::processLeftParenthesis()
//{
//    // push a left parenthesis onto the operator stack
//    m_stack.push(m_next);
//}
//
//void InfixToPostfixConverter::processRightParenthesis()
//{
//    // move operators from the stack to the output buffer, until a left 
//    // parenthesis appears on the stack (the left parenthesis is discarded)
//    do
//    {
//        Token top = m_stack.top();
//
//        if (top.getTokenType() == TokenType::LBracket)
//            break;
//
//        m_stack.pop();
//        m_postfix.push_back(top);
//    } 
//    while (true);
//
//    // discard left parenthesis
//    m_stack.pop();
//}
//
//void InfixToPostfixConverter::processEndOfInput()
//{
//    // copy remaining elements from operator stack to postfix buffer
//    while (!m_stack.empty())
//    {
//        Token top = m_stack.top();
//        m_stack.pop();
//        m_postfix.push_back(top);
//    }
//}
//
//void  InfixToPostfixConverter::dumpStacks()
//{
//    // dump latest token
//    std::cout << m_next << "  ";
//
//    std::cout << "[";
//
//    if (m_stack.size() != 0) {
//        // need a copy of the stack
//        std::stack<Token> stack{ m_stack };
//        std::vector<Token> tmp{};
//        while (!stack.empty()) {
//            Token top = stack.top();
//            stack.pop();
//            tmp.push_back(top);
//        }
//
//        std::reverse(
//            std::begin(tmp),
//            std::end(tmp)
//        );
//
//        std::for_each(
//            std::begin(tmp),
//            std::prev(std::end(tmp)),
//            [](const Token& token) {
//                std::cout << token << ", ";
//            }
//        );
//
//        const Token& latest = tmp.back();
//        std::cout << latest;
//    }
//
//    std::cout << "]";
//
//    // fill gap equally spaced
//    const size_t MaxDistance = 20;
//    size_t size = m_stack.size();
//    size_t count{};
//
//    if (size == 0) {
//        count = MaxDistance - 2;
//    }
//    else if (size == 1) {
//        count = MaxDistance - 3;
//    }
//    else {
//        count = MaxDistance - (3 * size);
//    }
//
//    for (size_t n{}; n != count; ++n) {
//        std::cout << " ";
//    }
//
//    std::cout << '[';
//    if (m_postfix.size() != 0) {
//
//        std::for_each(
//            std::begin(m_postfix),
//            std::prev(std::end(m_postfix)),
//            [](const Token& token) {
//                std::cout << token << ", ";
//            }
//        );
//
//        const Token& latest = m_postfix.back();
//        std::cout << latest;
//    }
//
//    std::cout << ']';
//    std::cout << std::endl;
//}

// =====================================================================================
// End-of-File
// =====================================================================================
