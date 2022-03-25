// =====================================================================================
// BinomialCoefficient.h
// =====================================================================================

#pragma once

class BinomialCoefficient
{
private:
	size_t m_n;
	size_t m_k;
	size_t m_value;

public:
	// c'tors
	BinomialCoefficient ();
	BinomialCoefficient (size_t, size_t);

	// getter / setter
	size_t getUpperNumber() const;
	size_t getLowerNumber() const;
	void setUpperNumber(size_t n);
	void setLowerNumber(size_t n);
	size_t getValue() const;

	// public interface
	void calculate ();
	PrimeDictionary calculateLegendre () const;
};

// output
std::ostream& operator<< (std::ostream&, const BinomialCoefficient&);

// =====================================================================================
// End-of-File
// =====================================================================================
