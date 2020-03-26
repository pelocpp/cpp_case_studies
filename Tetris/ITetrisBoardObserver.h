class ITetrisBoardObserver {
public:
    // TODO: Wird der auch aufgerufen ?!?!?
    virtual ~ITetrisBoardObserver() {};
    virtual void update(const ViewCellList&) = 0;
};
