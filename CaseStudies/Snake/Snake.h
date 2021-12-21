// =====================================================================================
// XXX.h
// =====================================================================================


class Snake
{
private:
    COORD m_head;   // head
    COORD * m_tail;  // tail
    int m_len;      // length of tail

public:
    // c'tors / d'tor
    Snake();
    Snake(const Snake&);
    ~Snake();

    // getter
    COORD Head();

    // public interface
    void Draw(GameConsole & console) const;
    void Grow(COORD coord);
    bool Hits(COORD coord) const;
    void Move(Direction dir);

    // assignment operator
    Snake & operator= (const Snake & snake);

private:
    // private helper methods
    bool IsBorderCollision(COORD coord);
};

 // helper function
 bool operator== (const COORD & coord1, const COORD & coord2);


 // =====================================================================================
 // End-of-File
 // =====================================================================================