#include <iostream>
#include <string>
#include <string>

#include "Logger.h"

using namespace std;

void handleValue(int value)
{
	cout << "Integer: " << value << endl;
}
void handleValue(double value)
{
	cout << "Double: " << value << endl;
}
void handleValue(std::string value)
{
	cout << "String: " << value << endl;
}



// First version using pass-by-value
void processValues()	// Base case
{
	// Nothing to do in this base case.
}

template<typename T1, typename... Tn>
void processValues(T1 arg1, Tn... args)
{
	handleValue(arg1);
	processValues(args...);
}



//// Second version using pass-by-rvalue-reference
//void processValuesRValueRefs()	// Base case
//{
//	// Nothing to do in this base case.
//}
//
//template<typename T1, typename... Tn>
//void processValuesRValueRefs(T1&& arg1, Tn&&... args)
//{
//	handleValue(std::forward<T1>(arg1));
//	processValuesRValueRefs(std::forward<Tn>(args)...);
//}
//


int main___()
{
	processValues(1, 2, 3.56, "test", 1.1f);
	cout << endl;
	// processValuesRValueRefs(1, 2, 3.56, "test", 1.1f);

	return 0;
}
