// =====================================================================================
// PermutationArrayEx.h
// =====================================================================================

template <typename T>
class PermutationArrayEx
{
private:
    std::vector<Permutation<T>> m_array;

public:
    // c'tors/d'tor
    PermutationArrayEx() = default;

    PermutationArrayEx(int size) {
        m_array.reserve(size);
    }

    // getter
    int count() const { return static_cast<int>(m_array.size()); }

    // public interface
    void insert(const Permutation<T>&) {
        m_array.push_back(p);
    }

    void insertAll(char ch) {
        for (Permutation<T>& p : m_array) {
            p.insertAtFront(ch);
        }
    }

    // operator(s)
    Permutation<T> operator[] (int) const {
        return m_values[i];
    }

    // output
    //friend std::ostream& operator<< (std::ostream&, const PermutationArray&);
};

template <typename T>
inline std::ostream& operator<< (std::ostream& os, const PermutationArrayEx<T>& array) {
    for (int i = 0; i < array.count(); i++)
        os << array.m_array[i] << std::endl;

    os << '[' << array.count() << " permutations]" << std::endl;

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
