class ViewCellList {

public:
    using cells_vector = std::vector<ViewCell>;
    using const_iterator = cells_vector::const_iterator;

public:
     // c'tors
    ViewCellList() = default;

    // public interface
    int size() const;

    // TODO: std::find_if !!!! in der Implementierung
    void add(const ViewCell& cell);

    ViewCell at(int index) const;

    // TODO: implement operator[] ...

    const_iterator begin() const { return m_cells.begin(); }
    const_iterator end() const { return m_cells.end(); }

private:
    std::vector<ViewCell> m_cells;
};
