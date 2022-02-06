// =====================================================================================
// Scanner.h
// =====================================================================================

#pragma once

template <typename T>
class Scanner
{
private:
    const std::string token_regex = "([1-9][0-9]*)|[(]|[)]|\\+|\\-|\\*|\\/|\\%";

public:
    using iterator = std::list<Token<T>>::iterator;
    using const_iterator = std::list<Token<T>>::const_iterator;

private:
    std::string         m_line;
    std::list<Token<T>> m_tokens;
    std::regex          m_token_regex;

public:
    // c'tor
    Scanner() : m_line{}, m_token_regex{ token_regex } {}
     
    // setter
    void set(const std::string& line) {
        m_line = line;
    }

    // TODO : testen, ob man das das Objekt verändern kann (also die Zeichenkette..=
    const std::string& get() const {
        return m_line;
    }

    // iterator support
    iterator begin() { return m_tokens.begin(); }
    iterator end() { return m_tokens.end(); }

    const_iterator begin() const { return m_tokens.cbegin(); }
    const_iterator end() const { return m_tokens.cend(); }

    // public interface
    void scan()
    {
        m_tokens.clear();

        auto rbegin = std::sregex_iterator(
            std::begin(m_line),
            std::end(m_line),
            m_token_regex
        );

        auto rend = std::sregex_iterator();

        while (rbegin != rend)
        {
            std::smatch m = *rbegin;
            std::string token = m.str();

            Token<T> tok{};
            switch (token[0])
            {
            case '(':
                tok = Token<T>{ TokenType::LBracket };
                m_tokens.push_back(tok);
                break;

            case ')':
                tok = Token<T>{ TokenType::RBracket };
                m_tokens.push_back(tok);
                break;

            case '+':
                tok = Token<T>{ TokenType::Operator, OperatorType::AddOp };
                m_tokens.push_back(tok);
                break;

            case '-':
                tok = Token<T>{ TokenType::Operator, OperatorType::SubOp };
                m_tokens.push_back(tok);
                break;

            case '*':
                tok = Token<T>{ TokenType::Operator, OperatorType::MulOp };
                m_tokens.push_back(tok);
                break;

            case '/':
                tok = Token<T>{ TokenType::Operator, OperatorType::DivOp };
                m_tokens.push_back(tok);
                break;

            case '%':
                tok = Token<T>{ TokenType::Operator, OperatorType::ModOp };
                m_tokens.push_back(tok);
                break;

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
                long long tmp{ stoll(token) };
                T value{ static_cast<T>(tmp) };
                tok = Token<T>{ TokenType::Operand, value };
                m_tokens.push_back(tok);
                break;
            }
            default:
                m_tokens.push_back(tok);
                break;
            }

            ++rbegin;
        }
    }

    void scan_classic() 
    {
        m_tokens.clear();

        for (size_t i{}; i != m_line.size(); ++i)
        {
            char ch{ m_line[i] };
            Token<T> tok{};

            switch (ch)
            {
            case ' ':
                continue;

            case '(':
                tok = Token<T>{ TokenType::LBracket };
                m_tokens.push_back(tok);
                break;

            case ')':
                tok = Token<T>{ TokenType::RBracket };
                m_tokens.push_back(tok);
                break;

            case '+':
                tok = Token<T>{ TokenType::Operator, OperatorType::AddOp };
                m_tokens.push_back(tok);
                break;

            case '-':
                tok = Token<T>{ TokenType::Operator, OperatorType::SubOp };
                m_tokens.push_back(tok);
                break;

            case '*':
                tok = Token<T>{ TokenType::Operator, OperatorType::MulOp };
                m_tokens.push_back(tok);
                break;

            case '/':
                tok = Token<T>{ TokenType::Operator, OperatorType::DivOp };
                m_tokens.push_back(tok);
                break;

            case '%':
                tok = Token<T>{ TokenType::Operator, OperatorType::ModOp };
                m_tokens.push_back(tok);
                break;

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
                T value{};
                while (i != m_line.size() && std::isdigit(m_line[i]))
                {
                    value = 10 * value + (m_line[i] - '0');
                    ++i;
                }

                // adjust index
                i--;

                tok = Token<T>{ TokenType::Operand, value };
                m_tokens.push_back(tok);
                break;
            }

            default:
                m_tokens.push_back(tok);
            }
        }
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
