// =====================================================================================
// JosephusEx.h
// =====================================================================================

#pragma once

constexpr size_t NumSoldiers = 41;

class JosephusEx
{
private:
    const size_t DefaultPassBy = 10;   // default "decimatio"

    size_t m_count;                    // total number of soldiers
    size_t m_alive;                    // number of alive soldiers
    size_t m_lastEliminated{ 0 };      // last eliminated soldier
    size_t m_lastAlive{ 0 };           // number of surviving soldier
    size_t m_passby{ DefaultPassBy };  // "decimatio"

    //std::forward_list<Soldier> m_soldiers;

     // array of boolean states: alive or not
    std::array<bool, NumSoldiers> m_soldiers{ true };   // mit false und true ausprobieren !!!!!!!!!
    size_t m_current;  // current index into array

public:
    // c'tors
    JosephusEx();
   // JosephusEx(size_t count);

    // getter/setter
    size_t count() const { return m_count; }
    size_t alive() const { return m_alive; }
    size_t lastEliminated() const { return m_lastEliminated; }
    size_t lastAlive();
    size_t passBy() const { return m_passby; }
    void setPassBy(int passby) { m_passby = passby; }

    // pubic interface
    bool eliminateNextSoldier();

private:
    // private helper methods
    void initScenario();
    void moveToNextAliveSoldier();
    void nextIndex();

    // output
    friend std::ostream& operator<< (std::ostream&, JosephusEx&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
