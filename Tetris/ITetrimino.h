class ITetrimino {
    // predicates
    virtual bool CanSetToTop() = 0;
    virtual bool CanMoveLeft() = 0;
    virtual bool CanMoveRight() = 0;
    virtual bool CanMoveDown() = 0;
    virtual bool CanRotate() = 0;
    virtual bool IsCoordinateWithin(int row, int col) = 0;

    // movement specific methods
    virtual void SetToTop() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;
    virtual bool MoveDown() = 0;
    virtual void Rotate() = 0;

    // board specific methods
    virtual void Set() = 0;
    virtual void Delete() = 0;
};