#include <iostream>
//#include <iomanip>
//#include <string>
//#include <algorithm>
//#include <list>
//#include <numeric>
#include <type_traits>
//#include <stdexcept>
//#include <regex>
//#include <random>
//#include <variant>
//#include <chrono>

// Diese beiden Includes weg ... die müssen in den jeweiligen h files drin sein ...
#include "ChainArithmetic.h"
#include "Token.h"

namespace ChainArithmetic_Modern {

    class ChainCalculatorModern
    {
    private:
        long long m_result;     // long long: Hmmm, geht das irgendwie anders  // evtl.  std::commmon_type
        char m_nextOperator;
        bool m_expectedOperator;

    public:
        // c'tors
        ChainCalculatorModern();

        // getter
        auto getResult() { return m_result; }

    public:
        void calc(auto ... args);

    private:

        // geht hier auch
        // calc(concept auto arg)   , also das ganze mit einem führenden concept ?????? 

        void calc(auto arg);
    };
}