#pragma once

class ITetrisBoard {

public:
    // getter/setter
    virtual int getNumRows() = 0;
    virtual int getNumColumns() = 0;

    virtual TetrisCell getCell(int row, int col) = 0;
    virtual void setCell(int row, int col, const TetrisCell& cell) = 0;
    
    // public interface
    virtual void clear() = 0;

    //void PostChanges(ViewCellList list);
    //bool IsBottomRowComplete();
    //void MoveNonEmptyRowsDown();


    // observer 
    // virtual  void attach(Observer observer) = 0;
    // virtual  void detach(Observer observer) = 0;
};