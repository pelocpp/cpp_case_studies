// =====================================================================================
// Program.cpp
// =====================================================================================

#include "ConstExpr.h"

int main()
{
    ConstExprComplex::testComplex();
    ConstExprComplexTemplate::testComplexTemplate();
    ConstExprPow::testPower();
    ConstExprCollatz::testCollatz();
    ConstExprCollatzInheritance::testCollatzInheritance();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
