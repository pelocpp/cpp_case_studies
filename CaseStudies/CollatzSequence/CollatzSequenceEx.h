// =====================================================================================
// CollatzSequenceEx.h
// =====================================================================================

// forward declaration of iterator class
template <typename T> 
class CollatzIteratorEx;

template <typename T> 
class CollatzSequenceEx
{
private:
    T m_start{ 1 };

public:
    // c'tor(s)
    CollatzSequenceEx() = default;
    CollatzSequenceEx(T start) : m_start{ start } {}

    // iterator support
    CollatzIteratorEx<T> begin() const { return { m_start }; }
    CollatzIteratorEx<T> end() const { return { T{ 1 } }; }
};

// =====================================================================================
// End-of-File
// =====================================================================================
