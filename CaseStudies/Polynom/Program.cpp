// =====================================================================================
// Program.cpp
// =====================================================================================

// TODO: Braucht es den Copy Kontruktor ???

// TODO: ES muss ein Template gemacht werden

// TODO: ES muss ein Concept für den Datentyp gemacht werden

// TODO: Hmmm, das Beispiel würde sich für den "Rocket" Operator <=> anbieten 

// TODO: Operator+:  Wozu diese beiden komischen Zeilen:

// TODO: Beschreiben: The correct way: There are two ways to loop backward correctly, the first one is :
// https://jdhao.github.io/2017/10/07/loop-forward-backward-with-cpp-vector/

// TODO:     Polynom(std::vector<double> coefficients);  // TODO: Brauchen wir den ????
// Es gibt da ja die Initializer_list 


#include <iostream>
#include <vector>

#include "Polynom.h"

void Testing_Ctors();
void Testing_Output();
void Testing_IsZero();
void Testing_UnaryPolynomOperators();

void Testing_PolynomAddition();
void Testing_PolynomSubtraction();

void Testing_PolynomMultiplication();
void Testing_AssignmentOperators();

void Testing_Evaluation_ArraySubscriptOperator();
void Testing_Evaluation_FunctionCallOperator();
void Testing_Evaluation_BothVariants();
void Testing_ComparisonOperators();
void Testing_Division();

int main()
{
    //Testing_Ctors();
    //Testing_Output();
    //Testing_IsZero();
    //Testing_UnaryPolynomOperators();

    Testing_PolynomAddition();
    Testing_PolynomSubtraction();

    //Testing_PolynomMultiplication();
    //Testing_AssignmentOperators();
    //Testing_Evaluation_ArraySubscriptOperator();
    //Testing_Evaluation_FunctionCallOperator();
    //Testing_Evaluation_BothVariants();
    //Testing_ComparisonOperators();
    //Testing_Division();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
