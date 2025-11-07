// =====================================================================================
// ProgramBadApproachMatrix.cpp
// =====================================================================================

#include "BadApproachMatrix.h"

static void test_bad_matrix_00()
{
    BadApproachMatrix<double, 3, 3> matrix{ };
    matrix.print();

    BadApproachMatrix<double, 3, 3> matrix2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    matrix2.print();

    BadApproachMatrix<double, 2, 3> matrix3{ 1, 2, 3, 4, 5, 6 };
    matrix3.print();

    BadApproachMatrix<double, 3, 3> matrix4{ { 1, 2, 3 }, { 4, 5, 6 },  { 7, 8, 9 } };
    matrix4.print();

    BadApproachMatrix<double, 100, 100> largeMatrix{ };
}

void test_bad_matrix()
{
    test_bad_matrix_00();
}

// =====================================================================================
// End-of-File
// =====================================================================================
