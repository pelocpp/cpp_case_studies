// =====================================================================================
// Permutation.h
// =====================================================================================

class Permutation
{
private:
    std::vector<char> m_values;

public:
    // c'tors
    Permutation() = default;
    Permutation(const std::initializer_list<char>&);
    Permutation(const std::string_view);
    Permutation(const std::vector<char>&);
    ~Permutation() { std::cout << "d'tor Permutation" << std::endl; };

public:
    // getter
    int grade() const { return static_cast<int>(m_values.size()); }
    std::vector<char> getValues() const { return m_values; }

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
