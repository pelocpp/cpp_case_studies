#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using string_input = std::istream_iterator<std::string>;

void findAnagrams();
void testBackInserter();

void testBackInserter() {
    const int numbers[]{ 1, 2, 3, 4, 5 };

    std::vector<int> vec(3U, 0);

    std::copy(numbers, numbers+3, vec.begin());
}

int main() {
    testBackInserter();

    return 0;
}

void findAnagrams() {
    std::cout
        << "Anagram finding program:" << std::endl
        << "finds all words in a dictionary that can" << std::endl
        << "be formed with the letters of a given word."
        << std::endl << std::endl;

    std::cout
        << "First, enter the name of the file containing" << std::endl
        << "the dictionary: " << std::flush;

    std::string dictionary_name;
    std::cin >> dictionary_name;

    std::ifstream ifs(dictionary_name.c_str());
    if (!ifs.is_open()) {
        std::cout
            << "Could not open file named "
            << dictionary_name << std::endl;
        exit(1);
    }

    std::cout << "Reading the dictionary ..." << std::flush;

    std::vector<std::string> dictionary;
    std::copy(string_input(ifs), string_input(), std::back_inserter(dictionary));
    std::cout << "\nThe dictionary contains "
        << dictionary.size() << " words.\n\n";


    //std::cout << "Now type a word (or any string of letters),\n"
    //    << "and I'll see if it has any anagrams: " << std::flush;
    //for (string_input j(std::cin); j != string_input(); ++j) {
    //    std::string word = *j;
    //    sort(word.begin(), word.end());
    //    bool found_one = false;
    //    do {
    //        if (binary_search(dictionary.begin(),
    //            dictionary.end(),
    //            word)) {
    //            std::cout << "  " << word << std::endl;
    //            found_one = true;
    //        }
    //    } while (next_permutation(word.begin(), word.end()));
    //    if (!found_one)
    //        std::cout << "  Sorry, none found.\n";
    //    std::cout << "\nType another word "
    //        << "(or the end-of-file char to stop): " << std::flush;
    //}
}