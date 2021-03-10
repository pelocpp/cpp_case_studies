// =====================================================================================
// JosephusListImpl.h
// =====================================================================================

#pragma once

class JosephusListImpl : public Josephus
{
private:
    std::forward_list<Soldier> m_soldiers;
    std::forward_list<Soldier>::iterator m_current;

public:
    // c'tors
    JosephusListImpl();
    JosephusListImpl(size_t count, size_t passby);

    // getter/setter
    virtual size_t lastAlive() const override { return (*m_current).getNumber(); }

    // pubic interface
    bool eliminateNextSoldier();

private:
    // private helper methods
    void initScenario();

    // output
    friend std::ostream& operator<< (std::ostream&, const JosephusListImpl&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
