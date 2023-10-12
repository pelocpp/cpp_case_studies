//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <algorithm>
//#include <list>
//#include <numeric>
//#include <type_traits>
//#include <stdexcept>
//#include <regex>
//#include <random>
//#include <variant>
//#include <chrono>

#include "ChainArithmetic.h"
#include "Token.h"

namespace ChainArithmetic_STL {

    class ChainCalculator
    {
    private:
        OperandType  m_result;          // long long: Hmmm, geht das irgendwie anders  // evtl.  std::commmon_type
        OperatorType m_nextOperator;

    public:
        // c'tors
        ChainCalculator();

        // getter
        auto getResult();

        // public interface
        void calc(auto ... args);
    };
}