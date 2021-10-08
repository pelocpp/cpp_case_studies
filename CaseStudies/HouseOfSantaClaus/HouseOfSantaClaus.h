// =====================================================================================
// HouseOfSantaClaus.h
// =====================================================================================

#pragma once

class HouseOfSantaClaus
{
friend std::ostream& operator<< (std::ostream&, const HouseOfSantaClaus&); 

protected:
    static constexpr int Min = 111111111;
    static constexpr int Max = 155555552;

private:
    std::vector<int> m_solutions;

public:
    HouseOfSantaClaus() = default;
    ~HouseOfSantaClaus() = default;
    virtual void solve() = 0;
    size_t numberOfSolutions() const { return m_solutions.size(); }

protected:
    void addSolution(int number);

    // minimalistic 'template method' pattern
    bool isSolution(int number); 
    virtual void numberToDigits(int number) = 0;
    virtual bool checkValidRangeOfDigits() = 0;
    virtual bool checkSelfLoops() = 0;
    virtual bool checkValidEdges() = 0;
    virtual bool checkForDuplicateEdges() = 0;

private:
    void printSolution(std::ostream& os, int number) const;
};

// =====================================================================================
// End-of-File
// =====================================================================================