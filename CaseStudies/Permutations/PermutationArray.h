class PermutationArray
{
private:
    int m_size;
    int m_top;
    Permutation* m_array;

public:
    // c'tors/d'tor
    PermutationArray();
    PermutationArray(int count);
    PermutationArray(const PermutationArray&);
    ~PermutationArray();

    // getter
    int Size() { return m_size; }

    // public interface
    bool Insert(const Permutation& p);
    void InsertAll(char c);

    // operators
    PermutationArray& operator= (const PermutationArray& p);
    Permutation operator[] (int i) const;

    // output
    friend ostream& operator<< (ostream& os, const PermutationArray& a);
};