#pragma once

class TetrisBoard : public ITetrisBoard {

private:
    int m_numRows;
    int m_numCols;

    std::array<std::array<TetrisCell, Cols>, Rows> m_board;

    // TODO: Wie sieht das mit SMART POINTER AUS ??????
    std::list<ITetrisBoardObserver*> m_observer;

public:
    //c'tors
    TetrisBoard(int rows, int cols);

    // getter/setter
    int getNumRows() override;
    int getNumColumns() override;
    TetrisCell getCell(int row, int col) override;
    void setCell(int row, int col, const TetrisCell& cell) override;

    // public interface
    void clear() override;
    bool isBottomRowComplete() override;
    void moveNonEmptyRowsDown() override;

    // TODO: Parameter vom Typ Referenz oder per Value ?!?!?!?!
    // void postChanges(const ViewCellList& list) override;

    // implementation of interface 'ITetrisBoardListener'
    void attach(ITetrisBoardObserver* observer) override;
    void detach(ITetrisBoardObserver* observer) override;
    void notifyAll(const ViewCellList& list) override;

private:
    // private helper methods
    bool isRowEmpty(int i);
    void copySingleRow(ViewCellList& list, int row);
};
