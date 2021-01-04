// =====================================================================================
// CollatzSequence.h
// =====================================================================================

// forward declaration of iterator class
class CollatzIterator;

class CollatzSequence
{
private:
    int m_start{ 1 };

public:
    // c'tor(s)
    CollatzSequence() = default;
    CollatzSequence(int start);

    // iterator support
    CollatzIterator begin() const;
    CollatzIterator end()   const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
