// =====================================================================================
// PermutationEx.h
// =====================================================================================

template <typename T>
class PermutationEx
{
private:
    std::vector<T> m_values;

public:
    // c'tors
    PermutationEx() = default;

    PermutationEx(const std::initializer_list<T>& list) : m_values{ list } {}

    PermutationEx(const std::vector<T>& values) : m_values{ values } {}

    // getter
    int grade() const { 
        return static_cast<int>(m_values.size()); 
    }

    std::vector<T> getValues() const { return m_values; }

    // public interface
    void insertAtFront(T ch) {
        m_values.insert(m_values.begin(), ch);
    }

    PermutationEx<T> removeAt(int i) const {
        std::vector<T> tmp = m_values;
        tmp.erase(tmp.begin() + i);
        return PermutationEx<T>(tmp);
    }

    // operator(s)
    T operator[] (int i) const {
        return m_values[i];
    }
};

template <typename T>
inline std::ostream& operator<< (std::ostream& os, const PermutationEx<T>& p) {
    os << '[';
    for (int i = 0; i < p.grade(); i++)
    {
        os << p[i];
        if (i < p.grade() - 1)
            os << ',';

    }
    os << ']';
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
