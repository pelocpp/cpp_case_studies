// =====================================================================================
// PermutationCalculator.h
// =====================================================================================

class PermutationCalculator
{
private:
    Permutation m_p;
    PermutationArray m_array;

public:
    // c'tor
    PermutationCalculator();

    // getter/setter
    void setPermutation(const Permutation&);
    Permutation getPermutation();

    // public interface
    PermutationArray calculate(const Permutation&);
    void calculate();

    PermutationArray calculateEx(const Permutation&);

    // enumerator interface
    //void Reset();
    //bool MoveNext();
    //Permutation Current();

private:
    int faculty(int n) const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
