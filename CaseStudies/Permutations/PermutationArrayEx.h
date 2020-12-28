// =====================================================================================
// PermutationArrayEx.h
// =====================================================================================

template <typename T>
class PermutationArrayEx
{
private:
    std::vector<PermutationEx<T>> m_array;

public:
    // c'tors/d'tor
    PermutationArrayEx() = default;

    PermutationArrayEx(int size) {
        m_array.reserve(size);
    }

    // getter
    int count() const { return static_cast<int>(m_array.size()); }

    // public interface
    void insert(const PermutationEx<T>& p) {
        m_array.push_back(p);
    }

    void insertAll(char ch) {
        for (PermutationEx<T>& p : m_array) {
            p.insertAtFront(ch);
        }
    }

    // operator(s)
    PermutationEx<T> operator[] (int i) const {
        return m_array[i];
    }
};

template <typename T>
inline std::ostream& operator<< (std::ostream& os, const PermutationArrayEx<T>& array) {
    for (int i = 0; i < array.count(); i++)
        os << array[i] << std::endl;

    os << '[' << array.count() << " permutations]" << std::endl;

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
