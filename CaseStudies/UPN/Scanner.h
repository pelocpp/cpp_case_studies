// =====================================================================================
// Scanner.h
// =====================================================================================

#pragma once

template <typename T>
class Scanner
{
public:
    using iterator = std::list<Token<T>>::iterator;
    using const_iterator = std::list<Token<T>>::const_iterator;

private:
    std::string m_line;
    std::list<Token<T>> m_tokens;

public:
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
    void scan() {
        for (size_t i{}; i != m_line.size(); ++i)
        {
            char c{ m_line[i] };

            switch (c)
            {
            case ' ':
                continue;

            case '(':
            {
                Token<T> tok(TokenType::LBracket);
                m_tokens.push_back(tok);
            }
            break;

            case ')':
            {
                Token<T> tok(TokenType::RBracket);
                m_tokens.push_back(tok);
            }
            break;

            case '+':
            {
                Token<T> tok(TokenType::Operator, OperatorType::AddOp);
                m_tokens.push_back(tok);
            }
            break;

            case '-':
            {
                Token<T> tok(TokenType::Operator, OperatorType::SubOp);
                m_tokens.push_back(tok);
            }
            break;

            case '*':
            {
                Token<T> tok(TokenType::Operator, OperatorType::MulOp);
                m_tokens.push_back(tok);
            }
            break;

            case '/':
            {
                Token<T> tok(TokenType::Operator, OperatorType::DivOp);
                m_tokens.push_back(tok);
            }
            break;

            case '%':
            {
                Token<T> tok(TokenType::Operator, OperatorType::ModOp);
                m_tokens.push_back(tok);
            }
            break;

            case '0':
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
                int value{};
                while (i != m_line.size() && std::isdigit(m_line[i]))
                {
                    value = 10 * value + (m_line[i] - '0');
                    i++;
                }

                // adjust index
                i--;

                Token<T> tok(TokenType::Operand, value);
                m_tokens.push_back(tok);
            }
            break;
            }
        }
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
