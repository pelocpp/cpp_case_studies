// =====================================================================================
// Program.cpp
// =====================================================================================

void test01_Josephus();
void test02_Josephus();
void test03_Josephus();

void test10_Josephus();


// A) Fehler: test10_Josephus da stimmt die Ausgabe nicht ... wenn über IJosephus Pointer zugegriffen wird

// B) Fehler: test03_Josephus da stimmt die Ausgabe nicht ... implementierung falsch 

// C) Fehler: test10_Josephus da sollte ein smart pointer rein ...


void test_Josephus()
{
    test03_Josephus();
}

int main()
{   
    test_Josephus();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
