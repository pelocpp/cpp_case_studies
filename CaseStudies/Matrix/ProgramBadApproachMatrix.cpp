// =====================================================================================
// ProgramBadApproachMatrix.cpp
// =====================================================================================

#include "BadApproachMatrix.h"

void test_000()
{
    BadApproachMatrix<double, 3, 3> matrix{ };
    matrix.print();

    BadApproachMatrix<double, 3, 3> matrix2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    matrix2.print();

    BadApproachMatrix<double, 2, 3> matrix3{ 1, 2, 3, 4, 5, 6 };
    matrix3.print();

    BadApproachMatrix<double, 3, 3> matrix4{ { 1, 2, 3 }, { 4, 5, 6 },  { 7, 8, 9 } };
    matrix4.print();
}

// =====================================================================================
// End-of-File
// =====================================================================================
