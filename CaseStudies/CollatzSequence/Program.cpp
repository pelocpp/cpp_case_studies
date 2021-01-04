// =====================================================================================
// Program.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

// https://stackoverflow.com/questions/8635844/assignment-operator-with-reference-class-member

// https://stackoverflow.com/questions/55940777/custom-iterator-for-use-in-stdsort
//https://www.walletfox.com/course/sortvectorofcustomobjects.php
//https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp   // seeeeeeeehr gut
//https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/

// http://cpp-tip-of-the-day.blogspot.com/2014/05/building-custom-iterators.html

// https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html // seeeeeeeehr gut // Chris Riesbeck

// SEHR GUTER TEXT
// https://davidgorski.ca/posts/stl-iterators/

// https://blog.galowicz.de/2016/09/04/algorithms_in_iterators/


/*********************

// However, the best practice for template classes and functions is to put the definition and the declaration together. 
// Mainly, there are two reasons
// 1. Compiler needs to know all the definition for any templates during compile time
// 2. Namescope is trivial to write and confusing

https://leimao.github.io/blog/CPP-Iterator/

Although I need a reference to the container to construct the edge_iterator, I store the pointer of the container.
I need a reference as the constructor parameter, because I want to make sure that I have a container.
I need to store a pointer, otherwise the assignment operator would not compile.
edge_iterator& edge_iterator::operator= (const edge_iterator& rhs)
{
    m_curr_iter = rhs.m_curr_iter;
    m_container = rhs.m_container; // pointer, because ref cannot be copied
    return *this;
}

// ============================================
Da wird das Thema Ref und Ptr abgehandelt ......
http://cpp-tip-of-the-day.blogspot.com/2014/05/building-custom-iterators.html

// ============================================

Hmmm, und hier wird es mit einer Referenz gemacht ? !? !? !
https ://subscription.packtpub.com/book/programming/9781786465184/1/ch01lvl1sec13/enabling-range-based-for-loops-for-custom-types
// ============================================
Wrapping Algorithms into Iterators
https ://blog.galowicz.de/2016/09/04/algorithms_in_iterators/

// ============================================
Auch viele Details :
https://medium.com/@alejandrodanielnoel/making-a-custom-iterator-class-in-c-3424f74a7138
// ============================================


// da geht es viel im difference_type       
// https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits


*********************/

void Test01_Collatz();
void Test02_Collatz();
void Test03_Collatz();
void Test04_Collatz();
void Test05_Collatz();
void Test06_Collatz();
void Test07_Collatz();
void Test08_Collatz();

void Test_Collatz()
{
    //Test01_Collatz();
//Test02_Collatz();
    Test03_Collatz();
    //Test04_Collatz();
    //Test05_Collatz();
    //Test06_Collatz();
    //Test07_Collatz();
    //Test08_Collatz();
}

void Test01_Collatz_Ex();
void Test02_Collatz_Ex();
void Test03_Collatz_Ex();
void Test04_Collatz_Ex();
void Test05_Collatz_Ex();
void Test06_Collatz_Ex();
void Test07_Collatz_Ex();
void Test08_Collatz_Ex();

void Test_Collatz_Ex()
{
    Test01_Collatz_Ex();
    Test02_Collatz_Ex();
    Test03_Collatz_Ex();
    Test04_Collatz_Ex();
    Test05_Collatz_Ex();
    Test06_Collatz_Ex();
    Test07_Collatz_Ex();
    Test08_Collatz_Ex();
}

int main()
{   
    Test_Collatz_Ex();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
