// =====================================================================================
// KnightProblemBoard.h
// =====================================================================================

#pragma once

// =====================================================================================
// defining board of knight problem

template <typename T, int ROWS, int COLS>
class KnightProblemBoard
{
    using Row = std::array<int, COLS>;

public:
    KnightProblemBoard() {
        clearBoard();
    }

private:
    std::array<Row, ROWS> m_board;

private:
    void verifyCoordinate(const Coordinate<T>& coord) const {

        if constexpr (DoRangeCheck) {
            if (coord.getRow() >= ROWS || coord.getCol() >= COLS) {
                throw std::range_error("verifyCoordinate failed !!! ");
            }
        }
    }

public:
    int& at(const Coordinate<T>& coord) {
        verifyCoordinate(coord);
        return m_board[coord.getRow()][coord.getCol()];
    }

    const int& at(const Coordinate<T>& coord) const {
        verifyCoordinate(coord);
        return m_board[coord.getRow()][coord.getCol()];
    }

    void clearBoard() {
        std::for_each(m_board.begin(), m_board.end(), [](Row& row) {
            std::for_each(row.begin(), row.end(), [](auto& element) {
                element = 0;
                });
            });
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
