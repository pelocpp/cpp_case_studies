// =====================================================================================
// TextfileStatistics.h // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#pragma once
//
//#include <algorithm>       // std::generate
//#include <cctype>          // std::toupper
//#include <cstddef>         // std::size_t
//#include <fstream>         // std::ofstream
//#include <iostream>        // std::cout
//#include <numeric>         // std::accumulate
#include <string>          // std::string
#include <string_view>     // std::string_view
//#include <vector>          // std::vector

class TextfileStatistics
{
private:
    std::string_view m_fileName;

public:
    // c'tor
    TextfileStatistics();

    // getter / setter
    void setFilename(std::string_view fileName);
    std::string_view getFilename();

    // public interface
    void countWordFrequencies();
    void countWordFrequenciesCOW();
    void computeMostFrequentWords();
};

// =====================================================================================
// End-of-File
// =====================================================================================
