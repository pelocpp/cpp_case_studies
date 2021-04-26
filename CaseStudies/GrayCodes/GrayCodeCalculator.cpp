// =====================================================================================
// GrayCodeCalculator.cpp
// =====================================================================================

#include <iostream>
//#include <iomanip>
//#include <sstream>
#include <vector>
#include <list>
//#include <thread>
//#include <future>
//#include <atomic>
//#include <latch>
#include <algorithm> 

#include "GrayCodeCalculator.h"

std::vector<std::vector<bool>> GrayCodeCalculator::calculate(size_t length)
{
    if (length == 1) {
        return calculateRankOne();
    }
    else {
        std::vector<std::vector<bool>> tmp = calculate(length - 1);

        // allocate a new Gray Code list - twice a large
        // TO BE DONE
        // std::vector<std::vector<bool>> result(2 * tmp.size());
        std::vector<std::vector<bool>> result;

        // copy old entries ...
        // std::for_each einbauen !!!!!
        for (int i = 0; i < tmp.size(); i++) {
            // ... and prefix old entry with '0'
            std::vector<bool> v = tmp[i];
            std::vector<bool> ex = v;
            ex.insert(ex.begin(), false);
            result.push_back(ex);
        }

        // mirror old entries ...
        for (size_t i = tmp.size() - 1; i != (size_t)-1; --i) {
            // ... and prefix old entry with '1'
            std::vector<bool> v = tmp[i];
            std::vector<bool> ex = v;
            ex.insert(ex.begin(), true);
            result.push_back(ex);
        }

        return result;
    }
}

std::vector<std::vector<bool>> GrayCodeCalculator::calculateRankOne()
{
    std::vector<std::vector<bool>> list;

    // TODO: emplace back in list ?!?!?! Geht das ???
    std::vector<bool> v0(1);
    v0[0] = false;
    list.push_back(std::move(v0));

    std::vector<bool> v1(1);
    v1[0] = true;
    list.push_back(std::move(v1));

    // // TODO: list mit initialisierungs liste erstellen ....

    return list;
}

void GrayCodeCalculator::print(std::vector<std::vector<bool>> result)
{
    std::for_each(std::begin(result), std::end(result), [](std::vector<bool> code) {
        
        std::for_each(std::begin(code), std::end(code), [](bool bit) {

            std::cout << bit;

            }
        );

        std::cout << std::endl;

        }
    );
}

// =====================================================================================
// End-of-File
// =====================================================================================
