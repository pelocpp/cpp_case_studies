class PermutationArray
{
private:
    //int m_size;
    //int m_top;
    //Permutation* m_array;
    std::vector<Permutation> m_array;

public:
    // c'tors/d'tor
    PermutationArray() = default;
    PermutationArray(int);
    //PermutationArray(const PermutationArray&);
    //~PermutationArray();

    // getter/setter
    int count() const { return static_cast<int>(m_array.size()); }

    // TODO: Really needed ????
    void setCapacity(int size);
    int getCapacity() const;

    // public interface
    void Insert(const Permutation&);
    void InsertAll(char);

    // operators
  //  PermutationArray& operator= (const PermutationArray& p);
    Permutation operator[] (int i) const;

    // output
    friend std::ostream& operator<< (std::ostream& os, const PermutationArray& a);
};