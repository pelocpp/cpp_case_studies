#include<iostream>
#include <variant>
using namespace std;

class B {
public:
    int f(int i) { cout << "f(int): "; return i + 1; }
    // ...
};
class D : public B {
public:
    using B::f; // make every f from B available

    double f(double d) { cout << "f(double): "; return d + 1.3; }
    // ...
}; 
//
//int main() {
//    D* pd = new D;
//    cout << pd->f(2) << '\n';
//    cout << pd->f(2.3) << '\n';
//    delete pd;
//}