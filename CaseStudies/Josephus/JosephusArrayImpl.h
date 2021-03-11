// =====================================================================================
// JosephusArrayImpl.h
// =====================================================================================

#pragma once

class JosephusArrayImpl : public Josephus
{
private:
    // array of boolean states: alive or not
    std::array<bool, NumSoldiers> m_soldiers{ }; 
    size_t m_current;  // current index into array

public:
    // c'tors
    JosephusArrayImpl();
    JosephusArrayImpl(size_t count, size_t passby);

    // public interface
    virtual bool eliminateNextSoldier() override;

private:
    // private helper methods
    void init();
    void moveToNextAliveSoldier();
    void nextIndex();

    // output
    friend std::ostream& operator<< (std::ostream&, JosephusArrayImpl&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
