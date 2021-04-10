// =====================================================================================
// Palindrom.h
// =====================================================================================

#pragma once

class Palindrom
{
private:
    Number m_start;
    int m_steps;

public:
    // c'tors 
    Palindrom();

public:
    // getter / setter
    void setStart(const Number&);
    Number getStart() const;
    void setSteps(int);
    int getSteps() const;

    // public interface
    std::tuple<Number, Number, int> calcPalindrom() const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
