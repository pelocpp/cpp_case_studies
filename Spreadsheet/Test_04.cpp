//#include<iostream>
//#include <variant>
//#include <string>
//
//template <class... Ts>
//struct Visitor;
//
//template <class T, class... Ts>
//struct Visitor<T, Ts...> : T, Visitor<Ts...>
//{
//    Visitor(T t, Ts... rest) : T(t), Visitor<Ts...>(rest...) {}
//
//    using T::func;
//    using Visitor<Ts...>::func;
//
//    void func(const T&)
//    {
//        // Whatever...
//    }
//};
//
//template <class T>
//struct Visitor<T> : T
//{
//    Visitor(T t) : T(t) {}
//
//    using T::func;
//
//    void func(const T&)
//    {
//        // Whatever...
//    }
//};
//
//
//int main() {
//
//    Visitor <std::string> abc(std::string("123"));
//}
//
