// =====================================================================================
// PermutationArray.h
// =====================================================================================

class PermutationArray
{
private:
    std::vector<Permutation> m_array;

public:
    // c'tors/d'tor
    PermutationArray() = default;
    PermutationArray(int);

    // getter
    int count() const { return static_cast<int>(m_array.size()); }

    // public interface
    void insert(const Permutation&);
    void emplace(std::string_view&&) noexcept;
    void emplace(std::initializer_list<char>&&) noexcept;
    void insertAll(char);

    // operator(s)
    Permutation operator[] (int) const;

    // output
    friend std::ostream& operator<< (std::ostream&, const PermutationArray&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
