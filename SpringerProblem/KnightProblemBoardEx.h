// =====================================================================================
// KnightProblemBoardEx.h
// =====================================================================================

#pragma once

// =====================================================================================
// defining board of knight problem

template <int ROWS, int COLS>
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
    void verifyCoordinate(const Coordinate& coord) const {

        if constexpr (DoRangeCheck) {
            if (getRow(coord) >= ROWS || getCol(coord) >= COLS) {
                throw std::range_error("verifyCoordinate failed !!! ");
            }
        }
    }

public:
    int& at(const Coordinate& coord) {
        verifyCoordinate(coord);
        return m_board[getRow(coord)][getCol(coord)];
    }

    const int& at(const Coordinate& coord) const {
        verifyCoordinate(coord);
        return m_board[getRow(coord)][getCol(coord)];
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
