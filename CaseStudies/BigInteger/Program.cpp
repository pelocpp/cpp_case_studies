// =====================================================================================
// Program.cpp
// =====================================================================================

// TODO: soll das Array size_t oder int enthalten ????????????? Nein:  usize8


// TODO: Cardinality muss size_t sein !!!!


// TODO: Warum sind die privat:
    // private helper operator
//int& operator[] (int);  // subscript operator
//const int& operator[] (int) const; // const subscript operator
// Hier würde sich ein iterator anbieten :)



#include <iostream>

void Test_Script_01();
void Test_Script_02();
void Test_Script_03();

void Test_Division();
void Test_DivisionPowerByTwo();
void Test_Faculty_01(size_t limit);
void Test_Faculty_02(long long limit);
void Test_Power(int limit);

void Test_Mersenne_01();
void Test_Mersenne_02();

void Test_Formatting_Output();

void Test_TypeConversionOperators();

void Test_Literals();

void Test_01_PerfectNumbers();
void Test_02_PerfectNumbers();
void Test_03_PerfectNumbers();

void Test_Range();
void Test_Range(int max);
void Test_Factorize_01();
void Test_Factorize_02();
void Test_Factorize_03();
void Test_Factorize_04();


int main()
{   
    Test_Factorize_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
