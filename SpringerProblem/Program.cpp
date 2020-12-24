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

void test_examples();

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    test_examples();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
