// =====================================================================================
// LoremIpsum.h // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#pragma once

#include <string>

// Generates a random word.
std::string generateWord();

// Generate a random sentence.
// Takes in an int minNumWords and an int maxNumWords, which are by default 4 and 12.
//   minNumWords: minimum number of words
//   maxNumWords: maximum number of words
std::string generateSentence(int minNumWords, int maxNumWords);

// Generate a random paragraph.
// Takes in four ints: minNumSentences, maxNumSentences, minNumWords, and maxNumWords.
// By default 5, 8, 4, and 12.
//   minNumSentences: minimum number of sentences
//   maxNumSentences: maximum number of sentences
//   minNumWords: minimum number of words per sentence
//   maxNumWords: maximum number of words per sentence
std::string generateParagraph(int minNumSentences, int maxNumSentences, int minNumWords, int maxNumWords);

// Generate multiple paragraphs
// Takes in five ints: paraCount, minSent, maxSent, minWord, and maxWord.
// By default 5, 5, 8, 4, and 12.
//   paraCount : number of paragraphs
//   rest explained in above function
std::string generateParagraphList(int paraCount = 5, int minSent = 5, int maxSent = 8, int minWord = 4, int maxWord = 12);



// =====================================================================================
// End-of-File
// =====================================================================================
