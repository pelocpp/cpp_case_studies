class ITetrisBoardListener {
public:
    virtual ~ITetrisBoardListener() {};

    // TODO: Kl�ren, ob die beiden observer Zeiger const vereinbart werden k�nnen ?!?!?!

    virtual void attach(ITetrisBoardObserver* observer) = 0;
    virtual void detach(ITetrisBoardObserver* observer) = 0;
    virtual void notifyAll(const ViewCellList& list) = 0;
};
