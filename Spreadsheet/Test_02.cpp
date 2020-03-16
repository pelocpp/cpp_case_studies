//#include<iostream>
//#include <variant>
//#include <string>
//
//
//
//// https://pabloariasal.github.io/2018/06/26/std-variant/
//
////struct Visitor
////{
////    void operator()(int a)
////    {
////        //Called if variant holds an int
////    }
////    void operator()(float a)
////    {
////        //Called if variant holds a float
////    }
////    void operator()(char a)
////    {
////        //Called if variant holds a char
////    }
////};
//
////auto visitor = make_visitor(
////    [](int b)
////    {
////        //Called if variant holds an int
////    },
////    [](float b)
////    {
////        //Called if variant holds a float
////    },
////        [](char b)
////    {
////        //Called if variant holds a char
////    }
////    );
//
////template<typename ...Ts>
////struct Visitor : Ts...
////{
////    Visitor(const Ts&... args) : Ts(args)...
////    {
////    }
////};
////
////template<typename ...Ts>
////auto make_visitor(Ts... lamdbas)
////{
////    return Visitor<Ts...>(lamdbas...);
////}
//
//template<typename T>
//void ff(const T& t)
//{
//    std::cout << t << std::endl;
//}
//
//template<typename T, typename ...Ts>
//void ff(const T& head, const Ts&... tail)
//{
//    std::cout << head << std::endl;
//    ff(tail...);
//}
//
//template <class... Ts>
//struct Visitor;
//
//template <class T, class... Ts>
//struct Visitor<T, Ts...> : T, Visitor<Ts...>
//{
//    Visitor(T t, Ts... rest) : T(t), Visitor<Ts...>(rest...) {}
//
//    using T::operator();
//    using Visitor<Ts...>::operator();
//};
//
//template <class T>
//struct Visitor<T> : T
//{
//    Visitor(T t) : T(t) {}
//
//    using T::operator();
//
//    void operator() () {
//        std::cout << "bin hier ..." << std::endl;
//    }
//};
//
//class MyString : public std::string {
//
//private:
//    std::string m_s;
//
//public:
//    MyString(std::string s) {
//        m_s = s;
//    }
//
//    std::string_view operator()() {
//
//        std::string_view sv = *this;
//        return sv;
//    }
//
//
//};
//
//int main() {
//
//    // ff(1, 2, 34);
//
//    Visitor<MyString, MyString> v(MyString("123"), MyString("456"));
//
//    //std::cout << v << std::endl;
//}
//
