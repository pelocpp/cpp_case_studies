// =====================================================================================
// PermutationEx.h
// =====================================================================================

class PermutationEx
{
private:
    std::vector<char> m_values;

public:
    // c'tors
    Permutation() = default;
    Permutation(const std::vector<char>);
    Permutation(const std::string_view s);

    // getter
    int grade() const { return static_cast<int>(m_values.size()); }

    // public interface
    void insertAtFront(char c);
    Permutation removeAt(int i) const;

    // operator(s)
    char operator[] (int i) const;

    // output
    friend std::ostream& operator<< (std::ostream&, const Permutation&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
