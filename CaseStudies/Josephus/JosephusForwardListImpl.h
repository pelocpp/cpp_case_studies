// =====================================================================================
// JosephusForwardListImpl.h
// =====================================================================================

#pragma once

class JosephusForwardListImpl : public Josephus
{
private:
    // linked list of Soldier objects
    std::forward_list<Soldier> m_soldiers;
    std::forward_list<Soldier>::iterator m_current;

public:
    // c'tors
    JosephusForwardListImpl();
    JosephusForwardListImpl(size_t count, size_t passby);

    // public interface
    virtual bool eliminateNextSoldier() override;

private:
    // private helper methods
    void init();

    // output
    friend std::ostream& operator<< (std::ostream&, const JosephusForwardListImpl&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
