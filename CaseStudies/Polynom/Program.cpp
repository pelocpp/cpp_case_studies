// =====================================================================================
// Program.cpp
// =====================================================================================

// no-template version
void test_Ctors();
void test_RemoveTrailingZeros();
void test_Output();
void test_Zero();
void test_Rank();
void test_UnaryPolynomOperators();
void test_Addition();
void test_Subtraction();
void test_Multiplication();
void test_Division();
void test_Modulo();
void test_AssignmentOperators();
void test_Evaluation();
void test_ComparisonOperators();
void test_SimpleStress();

// template version
void test_Ctors_Ex();
void test_RemoveTrailingZeros_Ex();
void test_Output_Ex();
void test_Zero_Ex();
void test_Rank_Ex();
void test_UnaryPolynomOperators_Ex();
void test_Addition_Ex();
void test_Subtraction_Ex();
void test_Multiplication_Ex();
void test_Division_Ex();
void test_Modulo_Ex();
void test_AssignmentOperators_Ex();
void test_Evaluation_Ex();
void test_ComparisonOperators_Ex();

// testing concepts
void test_Concepts();

void test() 
{
    test_Ctors();
    test_RemoveTrailingZeros();
    test_Output();
    test_Zero();
    test_Rank();
    test_UnaryPolynomOperators();
    test_Addition();
    test_Subtraction();
    test_Multiplication();
    test_Division();
    test_Modulo();
    test_AssignmentOperators();
    test_Evaluation();
    test_ComparisonOperators();
}

void testEx() 
{
    test_Ctors_Ex();
    test_RemoveTrailingZeros_Ex();
    test_Output_Ex();
    test_Zero_Ex();
    test_Rank_Ex();
    test_UnaryPolynomOperators_Ex();
    test_Addition_Ex();
    test_Subtraction_Ex();
    test_Multiplication_Ex();
    test_Division_Ex();
    test_Modulo_Ex();
    test_AssignmentOperators_Ex();
    test_Evaluation_Ex();
    test_ComparisonOperators_Ex();
}

int main()
{
    test();
    testEx();
    test_Concepts();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
