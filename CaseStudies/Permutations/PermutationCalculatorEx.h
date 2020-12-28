// =====================================================================================
// PermutationCalculatorEx.h
// =====================================================================================

template <typename T>
class PermutationCalculatorEx
{
private:
    PermutationEx<T> m_p;
    PermutationArrayEx<T> m_array;

public:
    // c'tor
    PermutationCalculatorEx() : m_p{}, m_array{} {}

    // getter/setter
    void setPermutation(const PermutationEx<T>& p) {
        m_p = p;
    }

    PermutationEx<T> getPermutation() {
        return m_p;
    }

    // public interface
    void calculate() {
        m_array = calculate(m_p);
    }

    PermutationArrayEx<T> calculate(const PermutationEx<T>& p) {
        if (p.grade() == 1)
        {
            PermutationArrayEx<T> a(1);
            a.insert(p);
            return a;
        }
        else
        {
            PermutationArrayEx<T> result(faculty(p.grade()));

            for (int i = 0; i < p.grade(); i++)
            {
                // create permutation without i.-th element of current permutation
                PermutationEx<T> q = p.removeAt(i);

                // calculate permutions of n-1 elements recursively
                PermutationArrayEx<T> tmp = calculate(q);

                // join result with removed character
                tmp.insertAll(p[i]);

                // append calculated permutations
                for (int m = 0; m < tmp.count(); m++)
                    result.insert(tmp[m]);
            }

            return result;
        }
    }

    // enumerator interface
    //void Reset();
    //bool MoveNext();
    //Permutation Current();

private:
    int faculty(int n) const {
        int result = 1;
        for (int i = 2; i <= n; i++)
            result *= i;

        return result;
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
