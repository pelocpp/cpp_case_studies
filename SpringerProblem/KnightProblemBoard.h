#pragma once

template <int Rows, int Cols>
class KnightProblemBoard
{
public:
    // TODO PeLo: c'tor missing !!!!!!!!!!!!!!!!
    // TODO PeLo: hübscher programmieren !!!

    KnightProblemBoard() {
        std::for_each(m_board.begin(), m_board.end(), [](auto& column) {
            std::for_each(column.begin(), column.end(), [](auto& element) {
                element = 0; 
                }
            );
            }
        );
    }

    //KnightProblemBoard( std::unique_ptr<KnightProblemBoard<Rows, Cols>> board ) {
    //    m_board = *board;
    //}


private:
    std::array<std::array<int, Cols>, Rows> m_board;

private:
    void verifyCoordinate(const Coordinate& coord) const {
        if (coord.getRow() >= Rows || coord.getCol() >= Cols) {
            throw std::range_error("verifyCoordinate failed !!! ");
        }
    }

public:
    int& at(const Coordinate& coord) {
        verifyCoordinate(coord);
        return m_board[coord.getCol()][coord.getRow()];
    }

    const int& at(const Coordinate& coord) const {
        verifyCoordinate(coord);
        return m_board[coord.getCol()][coord.getRow()];
    }

};