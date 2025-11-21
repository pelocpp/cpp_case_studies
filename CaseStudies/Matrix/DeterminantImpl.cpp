// =====================================================================================
// DeterminantImpl.cpp
// =====================================================================================

#include "Determinant.h"

// ist hier beschrieben
// https://www.youtube.com/watch?v=pyiKhRmvMF4

template Matrix<float>       minor<float>(Matrix<float>, std::size_t row, std::size_t col);
template Matrix<double>      minor<double>(Matrix<double>, std::size_t row, std::size_t col);
template Matrix<long double> minor<long double>(Matrix<long double>, std::size_t row, std::size_t col);

template float       determinant<float>       (Matrix<float>);
template double      determinant<double>      (Matrix<double>);
template long double determinant<long double> (Matrix<long double>);

// =====================================================================================
// End-of-File
// =====================================================================================
