class Permutation
{
private:
    char* m_values;
    int   m_length;

public:
    // c'tors / d'tor
    Permutation();
    Permutation(char[], int);
    Permutation(const Permutation&);
    ~Permutation();

    // getter
    int Grade() const { return m_length; }

    // public interface
    void Insert(char c);
    Permutation Remove(int i) const;

    // operators
    Permutation& operator= (const Permutation& p);
    char operator[] (int i) const;

    // output
    friend ostream& operator<< (ostream& os, const Permutation& p);
};