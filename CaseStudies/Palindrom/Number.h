// =====================================================================================
// Number.h
// =====================================================================================

#pragma once

class Number
{
private:
    std::vector<int> m_digits;

public:
    // c'tors / d'tor
    Number();
    explicit Number(std::string_view);

public:
    // getter
    size_t size() const;
    bool symmetric() const;

    // binary arithmetic addition operator
    friend Number operator+ (const Number&, const Number&);

    // functor (supporting formatted output)
    std::string operator()(int);   // ??????????????????????????
 
    // public interface
    Number add(const Number&) const;
    Number reverse() const;
   // void prependDigit(int digit);

private:
    // private helper methods
    void removeLeadingZeros();

    // output
    friend std::ostream& operator<< (std::ostream&, const Number&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
