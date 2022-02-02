// =====================================================================================
// Scanner.h
// =====================================================================================

#pragma once

class Scanner
{
    // Hmmmm, macht der wirklich Sinn ????
    friend std::ostream& operator<< (std::ostream&, const Scanner&);

private:
    std::string m_line;

    // ODER Std::vector ... oder std::forward_list ???
    std::list<Token> m_tokens;

public:
    // c'tor(s)
    //Scanner();

    // setter
    void set(const std::string&);
  //  int length();

    // public interface
    //bool hasMoreExpressions();
    //void readLine();
    std::list<Token> scan();

};

// =====================================================================================
// End-of-File
// =====================================================================================
