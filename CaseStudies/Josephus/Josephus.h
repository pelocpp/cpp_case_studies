// =====================================================================================
// Josephus.h
// =====================================================================================

#pragma once

// TODO wo gehört das letzten Endes hin ?????????????
constexpr size_t NumSoldiers = 17;    // default number of soldiers
constexpr size_t DefaultPassBy = 3;   // default "decimatio"

class Josephus : public IJosephus
{
protected:
    size_t m_count;                    // total number of soldiers
    size_t m_alive;                    // number of alive soldiers
    size_t m_lastEliminated{ 0 };      // last eliminated soldier
   // size_t m_lastAlive{ 0 };           // number of surviving soldier
    
    // size_t m_passby{ DefaultPassBy };  // "decimatio"
    size_t m_passby{ 1 };  // "decimatio"


public:
    // getter/setter
    virtual size_t count() const override { return m_count; }
    virtual size_t alive() const override { return m_alive; }
    virtual size_t lastEliminated() const override { return m_lastEliminated; }
    // virtual size_t lastAlive() const override { return m_lastAlive; }
    virtual size_t passBy() const override { return m_passby; }
    virtual void setPassBy(int passby) override { m_passby = passby; }

    // c'tors
    Josephus();
    Josephus(size_t count, size_t passby);
};

// =====================================================================================
// End-of-File
// =====================================================================================
