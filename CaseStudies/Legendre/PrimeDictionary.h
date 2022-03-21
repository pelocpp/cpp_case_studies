// =====================================================================================
// PrimeDictionary.h
// =====================================================================================

#pragma once

#include <iostream>
#include <unordered_map>

// TODO; Unterschied zwischen SetValue und Insert ?????????????
// TODO; Wozu getCount ß?????

class PrimeDictionary
{
private:
	std::unordered_map<size_t, size_t> m_map;

public:
	// getter
	size_t getCount() const;
	size_t getValue(size_t key) const;
	void setValue(size_t key, size_t value);

	// public interface
	bool insert (size_t key, size_t value);
	void reduce (const PrimeDictionary&);

	// output
	friend std::ostream& operator<< (std::ostream&, const PrimeDictionary&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
