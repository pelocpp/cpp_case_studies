// ===========================================================================
// Program.cpp // Pythagorean Triple Calculator
// ===========================================================================

#include <iostream>

#include "PythagoreanTripleCalculator.h"

static void test_pythagorean_triples_01()
{
    std::cout << "Main: " << std::this_thread::get_id() << std::endl;

    constexpr size_t Max = 2000;

    PythagoreanTripleCalculator seqCalc;
    {
        ScopedTimer watch{};
        seqCalc.calculateSeq(Max);
    }
    std::cout << seqCalc.toString() << std::endl;
    std::cout << "Done." << std::endl << std::endl;

    using ThreadsafeStack = ThreadsafeDataStore<PythagoreanTriple>;
    PythagoreanTripleCalculator<ThreadsafeStack> parCalc;
    {
        ScopedTimer watch{};
        parCalc.calculatePar(Max);
    }
    std::cout << parCalc.toString() << std::endl;
    std::cout << "Done." << std::endl;
}

int main()
{
    test_pythagorean_triples_01();
    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
