#include <iostream>
//#include <iomanip>
#include <string>
//#include <algorithm>
//#include <list>
//#include <numeric>
//#include <type_traits>
//#include <stdexcept>
#include <regex>
//#include <random>
//#include <variant>
//#include <chrono>

// Diese beiden Includes weg ... die müssen in den jeweiligen h files drin sein ...
#include "ChainArithmetic.h"
#include "Token.h"

namespace ChainArithmetic_Regex {

    class ChainCalculatorRegex
    {
    private:
        OperandType  m_result;          // long long: Hmmm, geht das irgendwie anders  // evtl.  std::commmon_type
        OperatorType m_nextOperator;
        std::string  m_regex;
        std::regex   m_tokens_regex;

    public:
        // c'tors
        ChainCalculatorRegex();

        // getter
        auto getResult() { return m_result; }

        // public interface
        void calc(std::string expression);


    private:

        Token<OperandType> getNextToken(std::sregex_iterator iter);
    };
}