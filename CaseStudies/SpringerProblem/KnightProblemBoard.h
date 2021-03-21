// =====================================================================================
// KnightProblemBoard.h
// =====================================================================================

#pragma once

// =====================================================================================
// defining 'KnightProblemBoard' template using 'inclusion model'

template <size_t ROWS, size_t COLS>
class KnightProblemBoard
{
private:
    std::array<std::array<int, COLS>, ROWS> m_board;

public:

    KnightProblemBoard() {
        clearBoard();
    }

private:
    void verifyCoordinate(const Coordinate& coord) const {

        if constexpr (RangeCheck) {
            if (coord.getRow() >= ROWS || coord.getCol() >= COLS) {
                throw std::range_error("verifyCoordinate failed !!! ");
            }
        }
    }

public:
    int& at(const Coordinate& coord) {
        verifyCoordinate(coord);
        return m_board[coord.getRow()][coord.getCol()];
    }

    const int& at(const Coordinate& coord) const {
        verifyCoordinate(coord);
        return m_board[coord.getRow()][coord.getCol()];
    }

    void clearBoard() {
        std::for_each(m_board.begin(), m_board.end(), [](auto& row) {
            std::for_each(row.begin(), row.end(), [](auto& element) {
                element = 0;
                });
            }
        );
    }
};

// =====================================================================================
// defining 'operator<<' for chess board

template <size_t ROWS, size_t COLS>
std::ostream& operator<< (std::ostream& os, const KnightProblemBoard<ROWS, COLS>& board) {

    for (size_t row{}; row != ROWS; ++row) {
        for (size_t col{}; col != COLS; ++col) {
            Coordinate coord{ row, col };
            int moveNumber{ board.at(coord) };
            os << std::setw(4) << moveNumber << ' ';
        }
        os << std::endl;
    }

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
