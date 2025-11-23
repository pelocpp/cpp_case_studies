// =====================================================================================
// MatrixInverterImpl.cpp
// =====================================================================================


//#include "FloatNumber.h"
#include "Vector.h"
#include "MatrixInverter.h"

#include <cstddef>
#include <stdexcept>

// getter/setter
template <typename T>
    requires FloatNumber<T>
void MatrixInverter<T>::set(const Matrix<T> matrix)
{
    if (matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("The matrix must be square!");
    }
}

// public interface
template <typename T>
    requires FloatNumber<T>
bool MatrixInverter<T>::invert()
{
    std::size_t n = m_matrix.rows();  // count of rows (or cols)

    Matrix<T> result{ n , n };
   
    // double[][] inverse = new double[n][n];

    for (int i = 0; i < n; i++) {
        // ei (Einheitsvektor)
        //double[] e = new double[n];
        //e[i] = 1.0;
        Vector<T> e{n};  // hmmm, sind da alles Nullen drin .....
        e[i] = T{ 1.0 };

        // L y = e
        // double[] y = forwardSubstitution(L, e);
        Vector<T> y = forwardSubstitution(e);

        // U x = y
        // double[] x = backwardSubstitution(U, y);
        Vector<T> x = backwardSubstitution(y);

        // xi als Spalte in A hoch -1 speichern
        //for (int row = 0; row < n; row++) {
        //    inverse[row][i] = x[row];
        //}

        for (int row = 0; row < n; row++) {
            result(row,i) = x[row];
        }
    }

    return true;
}


template <typename T>
    requires FloatNumber<T>
Vector<T> MatrixInverter<T>::forwardSubstitution(const Vector<T>& v)
{
    return {};
}

template <typename T>
    requires FloatNumber<T>
Vector<T> MatrixInverter<T>::backwardSubstitution(const Vector<T>& v)
{
    return {};
}

// =====================================================================================

// explicit template instantiations
template class MatrixInverter<float>;
template class MatrixInverter<double>;
template class MatrixInverter<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
