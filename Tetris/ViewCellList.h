class ViewCellList {

private:
    std::vector<ViewCell> m_cells;

public:
     // c'tors
    ViewCellList() = default;

    // public interface
    int size() const;

    // TODO: std::find_if !!!! in der Implementierung
    void add(ViewCell cell);

    ViewCell at(int index);

    // TODO: implement // add iterator interface !!!

    // TODO: implement operator[] ...
};

