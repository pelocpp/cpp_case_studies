// =====================================================================================
// Token.cpp
// =====================================================================================

#include <iostream>
#include <string>

#include "Token.h"

//Token::Token() : Token(TokenType::Null, OperatorType::NullOp, 0) {}
//
//Token::Token(TokenType type) : Token(type, OperatorType::NullOp, 0) {}
//
//Token::Token(TokenType type, OperatorType op) : Token(type, op, 0) {}
//
//Token::Token(TokenType type, int value) : Token (type, OperatorType::NullOp, value) {}
//
//Token::Token(TokenType type, OperatorType op, int value) 
//    : m_type{ type }, m_op{ op }, m_value{ value }
//{
//    switch (op)
//    {
//    case OperatorType::AddOp:
//    case OperatorType::SubOp:
//        m_precedence = 1;
//        break;
//    case OperatorType::MulOp:
//    case OperatorType::DivOp:
//    case OperatorType::ModOp:
//        m_precedence = 2;
//        break;
//    case OperatorType::NullOp:
//    default:
//        m_precedence = 0;
//    }
//}

//
//template <typename T>
//std::ostream& operator<< (std::ostream& os, const Token<T>& tok)
//{
//    switch (tok.m_type)
//    {
//    case TokenType::Operand:
//        os << tok.m_value;
//        break;
//
//    case TokenType::Operator:
//        switch (tok.m_op)
//        {
//        case OperatorType::AddOp:
//            os << '+';
//            break;
//        case OperatorType::SubOp:
//            os << '-';
//            break;
//        case OperatorType::MulOp:
//            os << '*';
//            break;
//        case OperatorType::DivOp:
//            os << '/';
//            break;
//        case OperatorType::ModOp:
//            os << '%';
//            break;
//        }
//        break;
//
//    case TokenType::LBracket:
//        os << '(';
//        break;
//
//    case TokenType::RBracket:
//        os << ')';
//        break;
//
//    default:
//        os << ' ';  // suited for debugging output
//        break;
//    }
//
//    return os;
//}

// =====================================================================================
// End-of-File
// =====================================================================================
