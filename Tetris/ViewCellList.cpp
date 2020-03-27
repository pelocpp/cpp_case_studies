#include <iostream>
#include <string>
#include <vector>

#include "CellColor.h"
#include "CellPoint.h"
#include "ViewCell.h"
#include "ViewCellList.h"

// c'tors
///ViewCellList::ViewCellList() {}

// public interface
int ViewCellList::size() const {
    return m_cells.size();
}

void ViewCellList::add(ViewCell cell) {

    // TODO: std::find_if !!!!

    // is location of this cell already present
    // warning C4018 : '<' : signed / unsigned mismatch

    for (int i = 0; i < m_cells.size(); i++) {

        ViewCell tmp = m_cells.at(i);
        //if (tmp.getPoint().equals(cell.getPoint())) {

        //    // replace this point with new cell (old one is obsolete)
        //    this.cells.set(i, cell);
        //    return;
        //}

        if (tmp.getPoint() == cell.getPoint()) {

            // replace this point with new cell (old one is obsolete)
            m_cells[i] = cell;
            return;
        }
    }

    // cell not found, just add it
    m_cells.push_back(cell);
}

ViewCell ViewCellList::at(int index) const {
    return m_cells.at(index);
}
