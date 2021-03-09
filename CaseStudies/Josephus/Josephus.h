// =====================================================================================
// Josephus.h
// =====================================================================================

#pragma once

class Josephus
{
private:
    const size_t DefaultPassBy = 10;   // default "decimatio"

    size_t m_count;                    // total number of soldiers
    size_t m_alive;                    // number of alive soldiers
    size_t m_lastEliminated{ 0 };      // last eliminated soldier
    size_t m_passby{ DefaultPassBy };  // "decimatio"

    std::forward_list<Soldier> m_soldiers;
    std::forward_list<Soldier>::iterator m_current;

public:
    // c'tors
    Josephus();
    Josephus(size_t count);

    // getter/setter
    size_t count() const { return m_count; }
    size_t alive() const { return m_alive; }
    size_t lastEliminated() const { return m_lastEliminated; }
    size_t lastAlive() const { return (*m_current).getNumber(); }
    size_t passBy() const { return m_passby; }
    void setPassBy(int passby) { m_passby = passby; }

    // pubic interface
    bool eliminateNextSoldier();

private:
    // private helper methods
    void initScenario();

    // output
    friend std::ostream& operator<< (std::ostream&, const Josephus&);
};

// =====================================================================================
// End-of-File
// =====================================================================================