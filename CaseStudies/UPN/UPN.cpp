//// =====================================================================================
//// UPN.cpp
//// =====================================================================================
//
//#include <iostream>
//#include <list>
//#include <stack>
//#include <string>
//
//#include "UPN.h"
//
//Token::Token() : m_type{ TokenType ::Null}, m_op{ OperatorType::NullOp }, m_value{ } {}
//
//Token::Token(TokenType type) : m_type{ type }, m_op{ OperatorType::NullOp }, m_value{ } {}
//
//Token::Token(TokenType type, OperatorType op) : m_type{ type }, m_op{ op }, m_value{ } {}
//
//// TODO ?????????????????????
//Token::Token(TokenType type, int value) : m_type{ TokenType::Operand }, m_op{ OperatorType::NullOp }, m_value{ value } {}
//
//std::ostream& operator<< (std::ostream& os, const Token& tok)
//{
//    switch (tok.m_type)
//    {
//    case TokenType::Operand:
//        os << tok.m_value;
//        break;
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
//    case TokenType::LBracket:
//        os << '(';
//        break;
//    case TokenType::RBracket:
//        os << ')';
//        break;
//    }
//
//    os << ' ';  // TODO ????????????????????? WOzu ???
//    return os;
//}
//
//
//
//// =====================================================================================
//// End-of-File
//// =====================================================================================
