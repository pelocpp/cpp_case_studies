// =====================================================================================
// LUDecompositionImpl.cpp
// =====================================================================================

#include "LUDecomposition.h"

#include <print>

// c'tor(s)
template <typename T>
    requires FloatNumber<T>
LU_Decomposition<T>::LU_Decomposition(const Matrix<T> matrix) 
    : m_matrix{ matrix }
{
    // initialize upper triangular matrix with input matrix
    m_upper = m_matrix;

    // initialize lower triangular matrix with a unit matrix
    m_lower = Matrix<T>{ m_matrix.rows(), m_matrix.cols() };
    m_lower.unit();

    // initialize permutation matrix with a unit matrix
    m_perm = Matrix<T>{ m_matrix.rows(), m_matrix.cols() };
    m_perm.unit();
}

// public interface
template <typename T>
    requires FloatNumber<T>
bool LU_Decomposition<T>::decompose_simple()
{
    // create an upper and lower triangular matrix
    for (std::size_t k{}; k != m_matrix.rows() - 1; ++k) {

        std::println("Pivot: {}", m_upper.at(k, k));

        if (m_upper.at(k, k) == 0.0) {
            return false;
        }

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_matrix.rows(); ++rowBelow) {

            T pivot{ m_upper.at(rowBelow, k) / m_upper.at(k, k) };
            m_upper.subtractRow(pivot, k, rowBelow);

            // set pivot element in lower triangular matrix
            m_lower(rowBelow, k) = pivot;
        }
    }

    return true;
}

template <typename T>
    requires FloatNumber<T>
bool LU_Decomposition<T>::decompose_pivot()
{
    // create an upper and lower triangular matrix
    for (std::size_t k{}; k != m_matrix.rows() - 1; ++k) {

        //// ==============================================
        //std::println("=================================");
        //std::println("{}", m_upper);
        //std::println("=================================");
        //// ==============================================

        std::size_t pivot{ m_upper.getIndexOfLargestAbsoluteValueInColumn(k, k) };
        if (pivot != k) {

            m_upper.swapRows(k, pivot);
            m_perm.swapRows(k, pivot);

            // If we perform the row swap in m_upper, we must also swap the multipliers
            // already obtained in m_lower for the columns < k accordingly

            //for (std::size_t j{}; j != k; ++j) {
            //    T tmp{ m_lower.at(k,j) };
            //    m_lower.at(k,j) = m_lower.at(pivot,j);
            //    m_lower.at(pivot,j) = tmp;
            //}

            m_lower.swapRowsBelowDiagonal(k, pivot);
        
            //// ============================================
            //std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
            //std::println("Upper: {}", m_upper);
            //std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
            //// ============================================

            //// ============================================
            //std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
            //std::println("Lower: {}", m_lower);
            //std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
            //// ============================================
        }

        T coeff{ m_upper.at(k, k) };
        // std::println("Coefficient: {}", coeff);

        if (coeff == 0.0) {
            return false;
        }

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_matrix.rows(); ++rowBelow) {

            T pivot{ m_upper.at(rowBelow, k) / m_upper.at(k, k) };
            m_upper.subtractRow(pivot, k, rowBelow);

            // set pivot element in lower triangular matrix
            m_lower(rowBelow, k) = pivot;
        }

        //// ============================================
        //std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        //std::println("Upper: {}", m_upper);
        //std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        //// ============================================

        //// ============================================
        //std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        //std::println("Lower: {}", m_lower);
        //std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        //// ============================================
    }

    return true;
}

template <typename T>
    requires FloatNumber<T>
void LU_Decomposition<T>::set(const Matrix<T> matrix)
{
    if (matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("The matrix must be square!");
    }

    m_matrix = matrix;
}

template <typename T>
    requires FloatNumber<T>
const Matrix<T>& LU_Decomposition<T>::getMatrix() const
{
    return m_matrix;
}

template <typename T>
    requires FloatNumber<T>
const Matrix<T>& LU_Decomposition<T>::getLowerMatrix() const
{
    return m_lower;
}

template <typename T>
    requires FloatNumber<T>
const Matrix<T>& LU_Decomposition<T>::getUpperMatrix() const
{
        return m_upper;
}

template <typename T>
    requires FloatNumber<T>
const Matrix<T>& LU_Decomposition<T>::getPermMatrix() const
{
    return m_perm;
}

// =====================================================================================

// explicit template instantiations
template class LU_Decomposition<float>;
template class LU_Decomposition<double>;
template class LU_Decomposition<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
