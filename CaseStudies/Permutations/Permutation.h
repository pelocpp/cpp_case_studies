class Permutation
{
private:
    //char* m_values;
    //int   m_length;
    std::vector<char> m_values;

public:
    // c'tors / d'tor
    Permutation() = default;
    Permutation(const std::vector<char>);
    Permutation(const std::string_view s);

    //Permutation(char[], int);
    //Permutation(const Permutation&);
    //~Permutation();

    // getter
    int Grade() const { return static_cast<int>(m_values.size()); }

    // public interface
    void Insert(char c);
    Permutation Remove(int i) const;

    // operators
    //Permutation& operator= (const Permutation& p);
    char operator[] (int i) const;

    // output
    friend std::ostream& operator<< (std::ostream& os, const Permutation& p);
};