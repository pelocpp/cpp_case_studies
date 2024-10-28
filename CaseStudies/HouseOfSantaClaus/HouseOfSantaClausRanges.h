// =====================================================================================
// HouseOfSantaClausRanges.h
// =====================================================================================

#pragma once

#include <array>

class HouseOfSantaClausRanges : public HouseOfSantaClaus
{
private:
	std::array<int, 9> m_digits{};

public:
	// c'tor
	HouseOfSantaClausRanges() = default;

public:
	virtual void solve() override;

protected:
	virtual void numberToDigits(int number) override;
	virtual bool checkValidRangeOfDigits() override;
	virtual bool checkSelfLoops() override;
	virtual bool checkValidEdges() override;
	virtual bool checkForDuplicateEdges() override;
};

// =====================================================================================
// End-of-File
// =====================================================================================
