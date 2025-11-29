// =====================================================================================
// LU_DecompositionImpl.cpp
// =====================================================================================

#include "LU_Decomposition.h"

#include <print>

// c'tor(s)
template <typename T>
    requires FloatNumber<T>
LU_Decomposition<T>::LU_Decomposition(const Matrix<T> matrix) 
    : m_matrix{ matrix }
{
    //m_lower = { m_matrix.rows() * m_matrix.cols() };
    //m_upper = { m_matrix.rows() * m_matrix.cols() };

    // initialize lower triangular matrix with a unit matrix
    m_lower = Matrix<T>{ m_matrix.rows(), m_matrix.cols() };
    for (std::size_t k{}; k != m_matrix.rows(); ++k) {
        m_lower(k, k) = T{ 1.0 };
    }

    // initialize upper triangular matrix with input matrix
    m_upper = m_matrix;
}

// public interface
template <typename T>
    requires FloatNumber<T>
bool LU_Decomposition<T>::decompose_simple()
{
    // create an upper and lower triangular matrix
    for (std::size_t k{}; k != m_matrix.rows() - 1; ++k) {

      //  std::println("Pivot: {}", m_upper.at(k, k));

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

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_matrix.rows(); ++rowBelow) {

            // ============================================
            std::println("=================================");
            std::println("{}", m_upper);
            std::println("=================================");
            // ============================================

            T coefficient{ m_upper.at(k, k) };

            std::println("Coefficient: {}", m_upper.at(k, k));

            if (coefficient == 0.0) {

                // need coefficient unequal zero
                bool foundCoefficient = false;
                for (std::size_t below{ k + 1 }; below != m_matrix.rows(); ++rowBelow) {

                    coefficient = m_upper.at(below, k);
                    if (coefficient != 0.0) {

                        m_upper.swapRows(k, below);
                        foundCoefficient = true;

                        // ============================================
                        std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
                        std::println("{}", m_upper);
                        std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
                        // ============================================

                        break;
                    }
                }

                if (!foundCoefficient) {
                    return false;
                }
            }

            T pivot{ m_upper.at(rowBelow, k) / m_upper.at(k, k) };
            m_upper.subtractRow(pivot, k, rowBelow);

            // set pivot element in lower triangular matrix
            m_lower(rowBelow, k) = pivot;
        }





       

        //if (m_upper.at(k, k) != 0.0) {

        //    // create a zero value in column 'k' in all rows beneath
        //    for (std::size_t rowBelow{ k + 1 }; rowBelow != m_matrix.rows(); ++rowBelow) {

        //        T pivot{ m_upper.at(rowBelow, k) / m_upper.at(k, k) };
        //        m_upper.subtractRow(pivot, k, rowBelow);

        //        // set pivot element in lower triangular matrix
        //        m_lower(rowBelow, k) = pivot;
        //    }
        //}
        //else {

        //    // need coefficient unequal zero
        //    bool foundCoefficient = false;
        //    std::size_t rowBelow{ k + 1 };
        //    for (; rowBelow != m_matrix.rows(); ++rowBelow) {

        //        T coefficient{ m_upper.at(rowBelow, k) };
        //        if (coefficient != 0.0) {

        //            m_upper.swapRows(k, rowBelow);
        //            foundCoefficient = true;
        //            break;
        //        }
        //    }

        //    if (!foundCoefficient) {
        //        return false;
        //    }

        //    // ============================================
        //    std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        //    std::println("{}", m_upper);
        //    std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        //    // ============================================

        //    T pivot{ m_upper.at(rowBelow, k) / m_upper.at(k, k) };
        //    m_upper.subtractRow(pivot, k, rowBelow);

        //    // set pivot element in lower triangular matrix
        //    m_lower(rowBelow, k) = pivot;
        //}
    }

    return true;
}


//template <typename T>
//    requires FloatNumber<T>
//bool LU_Decomposition<T>::decompose_pivot()
//{
//    // create an upper and lower triangular matrix
//    for (std::size_t k{}; k != m_matrix.rows() - 1; ++k) {
//
//        // ============================================
//        std::println("=================================");
//        std::println("{}", m_upper);
//        std::println("=================================");
//        // ============================================
//
//        std::println("Pivot: {}", m_upper.at(k, k));
//
//        if (m_upper.at(k, k) != 0.0) {
//
//            // create a zero value in column 'k' in all rows beneath
//            for (std::size_t rowBelow{ k + 1 }; rowBelow != m_matrix.rows(); ++rowBelow) {
//
//                T pivot{ m_upper.at(rowBelow, k) / m_upper.at(k, k) };
//                m_upper.subtractRow(pivot, k, rowBelow);
//
//                // set pivot element in lower triangular matrix
//                m_lower(rowBelow, k) = pivot;
//            }
//        }
//        else {
//
//            // need coefficient unequal zero
//            bool foundCoefficient = false;
//            std::size_t rowBelow{ k + 1 };
//            for (; rowBelow != m_matrix.rows(); ++rowBelow) {
//            
//                T coefficient{ m_upper.at(rowBelow, k) };
//                if (coefficient != 0.0) {
//
//                    m_upper.swapRows(k, rowBelow);
//                    foundCoefficient = true;
//                    break;
//                }
//            }
//
//            if (!foundCoefficient) {
//                return false;
//            }
//
//            // ============================================
//            std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
//            std::println("{}", m_upper);
//            std::println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
//            // ============================================
//
//            T pivot{ m_upper.at(rowBelow, k) / m_upper.at(k, k) };
//            m_upper.subtractRow(pivot, k, rowBelow);
//
//            // set pivot element in lower triangular matrix
//            m_lower(rowBelow, k) = pivot;
//        }
//    }
//
//    return true;
//}

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
void LU_Decomposition<T>::printMatrix() const
{
    // to be Done: Überladen von std::format // print a la C++ 23

    for (std::size_t col{}; auto elem : m_matrix) {

        std::print("{:6.4g}", elem);

        ++col;
        if (col % m_matrix.cols() == 0) {
            std::println();
        }
    }
}

template <typename T>
    requires FloatNumber<T>
void LU_Decomposition<T>::printLowerTriangularMatrix() const
{
    // to be Done: Überladen von std::format // print a la C++ 23

    for (std::size_t col{}; auto elem : m_lower) {

        std::print("{:6.4g}", elem);

        ++col;
        if (col % m_matrix.cols() == 0) {
            std::println();
        }
    }
}

template <typename T>
    requires FloatNumber<T>
void LU_Decomposition<T>::printUpperTriangularMatrix() const
{
    // to be Done: Überladen von std::format // print a la C++ 23

    for (std::size_t col{}; auto elem : m_upper) {

        std::print("{:6.4g}", elem);

        ++col;
        if (col % m_matrix.cols() == 0) {
            std::println();
        }
    }
}

// =====================================================================================

// explicit template instantiations
template class LU_Decomposition<float>;
template class LU_Decomposition<double>;
template class LU_Decomposition<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
