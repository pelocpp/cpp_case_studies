// =====================================================================================
// PrimeDictionary.h
// =====================================================================================

#pragma once

#include <iostream>
#include <unordered_map>

class PrimeDictionary
{
private:
	std::unordered_map<size_t, size_t> m_map;

public:
	// getter
	size_t get(size_t key) const;
	void set(size_t key, size_t value);

	// public interface
	void reduce (const PrimeDictionary&);

	// output
	friend std::ostream& operator<< (std::ostream&, const PrimeDictionary&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
