// =====================================================================================
// IJosephus.h
// =====================================================================================

#pragma once

class IJosephus
{
public:
    // getter/setter
    virtual size_t count() const = 0;
    virtual size_t alive() const = 0;
    virtual size_t lastEliminated() const = 0;
    virtual size_t lastAlive() const = 0;
    virtual size_t passBy() const = 0;
    virtual void setPassBy(int passby) = 0;

    // public interface
    virtual bool eliminateNextSoldier() = 0;
    virtual void eliminateAll() = 0;
};

// =====================================================================================
// End-of-File
// =====================================================================================
