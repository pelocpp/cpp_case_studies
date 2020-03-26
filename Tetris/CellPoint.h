class CellPoint {

private:
    int m_x;
    int m_y;

public:
    // c'tors
    CellPoint();
    CellPoint(int x, int y);

    // getter/setter
    int getX();
    int getY();
    void setX(int);
    void setY(int);

    // operators
    // TODO: muss der überschrieben weden ?? Value type
     //   public boolean equals(Object obj) {

    // operators
    friend bool operator== (const CellPoint&, const CellPoint&);

    // public interface
    std::string tostring();
};