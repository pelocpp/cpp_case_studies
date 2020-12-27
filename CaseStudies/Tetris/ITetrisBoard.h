#pragma once

class ITetrisBoard : public ITetrisBoardListener {

public:
    // getter/setter
    virtual int getNumRows() = 0;
    virtual int getNumColumns() = 0;

    virtual TetrisCell getCell(int row, int col) = 0;
    virtual void setCell(int row, int col, const TetrisCell& cell) = 0;
    
    // public interface
    virtual void clear() = 0;
    virtual bool isBottomRowComplete() = 0;
    virtual void moveNonEmptyRowsDown() = 0;


    // TODO: Parameter vom Typ Referenz oder per Value ?!?!?!?!
    // virtual void postChanges(const ViewCellList& list) = 0;
};