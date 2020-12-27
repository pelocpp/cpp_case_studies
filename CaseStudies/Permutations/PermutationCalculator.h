class PermutationCalculator
{
private:
    int m_index;
    Permutation m_perm;
    PermutationArray m_array;

public:
    // c'tor
    PermutationCalculator();

    // getter/setter
    void SetPermutation(const Permutation&);
    Permutation GetPermutation();

    // public interface
    PermutationArray Calculate(const Permutation& p);
    void Calculate();

    // enumerator interface
    void Reset();
    bool MoveNext();
    Permutation Current();

private:
    int Faculty(int n) const;
};