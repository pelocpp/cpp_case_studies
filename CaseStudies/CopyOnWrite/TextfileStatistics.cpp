// =====================================================================================
// TextfileStatistics.cpp // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#include "TextfileStatistics.h"

#include <print>   // std::println

constexpr std::string_view fileNameSmall       { "LoremIpsumSmall.txt" };
constexpr std::string_view fileNameLarge       { "LoremIpsumLarge.txt" };
constexpr std::string_view fileNameHuge        { "LoremIpsumHuge.txt" };
constexpr std::string_view fileNameVeryHuge    { "LoremIpsumVeryHuge.txt" };
constexpr std::string_view fileNameExtremeHuge { "LoremIpsumExtremeHuge.txt" };

static void main_textfile_statistics_01()
{
    TextfileStatistics stats;
    stats.setFilename(fileNameVeryHuge);
    stats.countWordFrequencies();
    std::println();
    stats.countWordFrequenciesCOW();
    std::println();
}

static void main_textfile_statistics_02()
{
    TextfileStatistics stats;
    stats.setFilename(fileNameVeryHuge);
    stats.computeMostFrequentWords();
    std::println();
    stats.computeMostFrequentWordsCOW();
    std::println();
}

void main_textfile_statistics()
{
    main_textfile_statistics_01();
    main_textfile_statistics_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
