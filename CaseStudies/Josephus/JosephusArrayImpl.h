// =====================================================================================
// JosephusArrayImpl.h
// =====================================================================================

#pragma once

class JosephusArrayImpl : public Josephus
{
private:
     
    std::array<bool, NumSoldiers> m_soldiers{ true }; // array of boolean states: alive or not
    size_t m_current;  // current index into array
    size_t m_lastAlive{ 0 };           // number of surviving soldier

public:
    // c'tors
    JosephusArrayImpl();
    JosephusArrayImpl(size_t count, size_t passby);

    // getter/setter
    virtual size_t lastAlive() const override;

    size_t LAST_ALIVE();

    // pubic interface
    bool eliminateNextSoldier();

private:
    // private helper methods
    void initScenario();
    void moveToNextAliveSoldier();
    void nextIndex();

    // output
    friend std::ostream& operator<< (std::ostream&, const JosephusArrayImpl&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
