// =====================================================================================
// Program.cpp
// =====================================================================================

// TODO: soll das Array size_t oder int enthalten ?????????????

// brauchen wir ein separates m_length: wohl eher n

// TODO: Cardinality muss size_t sein !!!!


// TODO: Warum sind die privat:
    // private helper operator
//int& operator[] (int);  // subscript operator
//const int& operator[] (int) const; // const subscript operator
// Hier w�rde sich ein iterator anbieten :)



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


void Test_Division();
void Test_Faculty(int limit);

int main()
{   
    Test_Faculty(31);
}

// =====================================================================================
// End-of-File
// =====================================================================================
