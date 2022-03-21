class BinomialCoefficient
{
private:
	long m_n;
	long m_k;
	long m_value;

public:
	// ctors
	BinomialCoefficient ();
	BinomialCoefficient (long n, long k);

	// getter / setter
	long GetUpperNumber();
	long GetLowerNumber();
	void SetUpperNumber(long n);
	void SetLowerNumber(long n);
	long GetValue();

	// public interface
	void Calculate ();
	PrimeDictionary CalculateLegendre ();
};
