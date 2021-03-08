// =====================================================================================
// Josephus.h
// =====================================================================================

#pragma once

class Josephus
{
    // output
    friend std::ostream & operator<< (std::ostream&, const Josephus&);

private:
    std::forward_list<Soldier> m_soldiers;

    std::forward_list<Soldier>::iterator m_current;

    const size_t DefaultPassBy = 10;  // default "decimatio"


public:
    // c'tors
    Josephus();
    Josephus(size_t count);


private:
    //int m_start{ 1 };
    //int m_current{ 1 };
    //int m_last{ };

    // TODO Fehlt Vorbelegung ...

    size_t m_count;           // total number of soldiers
    size_t m_alive;           // number of alive soldiers
    size_t m_lastEliminated;  // last eliminated soldier
    size_t m_passby;          // "decimatio"

public:
    // getter/setter
    size_t count() const { return m_count; }
    size_t alive() const { return m_alive; }
    size_t lastEliminated() const { return m_lastEliminated; }
    //size_t LastAlive() { return m_current->m_number; }
    size_t passBy() const { return m_passby; }
    void setPassBy(int passby) { m_passby = passby; }

    //// operators
    //int operator*() const;
    //CollatzIterator& operator++();
    //bool operator!=(const CollatzIterator&) const;

    // pubic interface
    bool eliminateNextSoldier();

private:
    // private helper methods
    void createLinkedList();
};

// =====================================================================================
// End-of-File
// =====================================================================================
