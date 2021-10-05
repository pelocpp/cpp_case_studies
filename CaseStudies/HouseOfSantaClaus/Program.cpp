// =====================================================================================
// Program.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <chrono>

#include "HouseOfSantaClaus.h"
#include "HouseOfSantaClausIterative.h"
#include "HouseOfSantaClausRanges.h"

void solveIterative();
void solveRangeBased();

int main()
{
	solveIterative();
	solveRangeBased();
	return 0;
}

void solveIterative()
{
	std::chrono::system_clock::time_point start { std::chrono::system_clock::now() };
	auto begin{ std::chrono::time_point_cast<std::chrono::milliseconds>(start) };
	HouseOfSantaClausIterative house;
	house.solve();
	std::chrono::system_clock::time_point stop{ std::chrono::system_clock::now() };
	auto end{ std::chrono::time_point_cast<std::chrono::milliseconds>(stop) };

	std::chrono::milliseconds duration{ end - begin };
	std::cout << "Iterative:   " << duration.count() << " msecs." << std::endl;
	std::cout << house;
	std::cout << "Solutions:   " << house.numberOfSolutions() << std::endl;
}

void solveRangeBased()
{
	std::chrono::system_clock::time_point start{ std::chrono::system_clock::now() };
	auto begin{ std::chrono::time_point_cast<std::chrono::milliseconds>(start) };
	HouseOfSantaClausRanges house;
	house.solve();
	std::chrono::system_clock::time_point stop{ std::chrono::system_clock::now() };
	auto end{ std::chrono::time_point_cast<std::chrono::milliseconds>(stop) };

	std::chrono::milliseconds duration{ end - begin };
	std::cout << "Range based: " << duration.count() << " msecs." << std::endl;
	std::cout << house;
	std::cout << "Solutions:   " << house.numberOfSolutions() << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
