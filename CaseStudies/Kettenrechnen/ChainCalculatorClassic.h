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

// Diese beiden Includes weg ... die müssen in den jeweiligen h files drin sein ...
#include "ChainArithmetic.h"
#include "Token.h"

namespace ChainArithmetic_Classic {

    class ChainCalculatorClassic
    {
    private:
        OperandType  m_result;          // long long: Hmmm, geht das irgendwie anders  // evtl.  std::commmon_type
        OperatorType m_nextOperator;
        std::string::iterator m_begin;
        std::string::iterator m_end;

    public:
        // c'tors
        ChainCalculatorClassic();

        // getter
        auto getResult() { return m_result; }

        // public interface
        void calc(std::string expression);

    private:
        Token<OperandType> getNextToken();
    };
}
