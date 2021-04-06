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

void Test_Sizes()
{
    size_t tmp;

    tmp = 123;

    return;
    //std::cout << sizeof(size_t) << std::endl;
    //std::cout << sizeof(SHRT_MIN) << std::endl;
    //std::cout << sizeof(SHRT_MAX) << std::endl;
    //std::cout << sizeof(USHRT_MAX) << std::endl;
    //std::cout << sizeof(INT_MIN) << std::endl;
    //std::cout << sizeof(INT_MAX) << std::endl;
    //std::cout << sizeof(UINT_MAX) << std::endl;
    //std::cout << sizeof(LONG_MIN) << std::endl;
    //std::cout << sizeof(LONG_MAX) << std::endl;
    //std::cout << sizeof(ULONG_MAX) << std::endl;
    //std::cout << sizeof(LLONG_MAX) << std::endl;
    //std::cout << sizeof(LLONG_MIN) << std::endl;
    //std::cout << sizeof(ULLONG_MAX) << std::endl;
}

void Test_Script_01();
void Test_Script_02();
void Test_Script_03();

void Test_Division();
void Test_DivisionPowerByTwo();
void Test_Faculty(int limit);
void Test_Faculty_0(int limit);
void Test_Power(int limit);

void Test_Mersenne_01();
void Test_Mersenne_02();

void Test_Formatting_Output();

void Test_TypeConversionOperators();

void Test_Literals();

void Test_01_PerfectNumbers();
void Test_02_PerfectNumbers();
void Test_03_PerfectNumbers();

int main()
{   
    Test_Faculty_0(31);
}

// =====================================================================================
// End-of-File
// =====================================================================================
