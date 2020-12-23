// =====================================================================================
// Program.cpp
// =====================================================================================

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


// =====================================================================================
// http://peterloos.de/index.php/m-multithreading/m-multithreading-tpl/58-a-mt-knights-problem
// =====================================================================================

// TODO: Die L�sungen als Event // mit Lambdas ausgeben ...
// TODO: Da werden viele Koordinaten by Value �bergeben ... geht das auch per Referenz

// =====================================================================================

void test_examples();
void test_examples_ex();

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    test_examples();
    test_examples_ex();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
