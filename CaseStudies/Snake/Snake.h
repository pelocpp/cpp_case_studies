// =====================================================================================
// Snake.h
// =====================================================================================

class Snake
{
private:
    static constexpr int InitialLength = 4;

private:
    COORD m_head;               // head
    std::vector<COORD> m_tail;  // tail

public:
    // c'tor
    Snake();

    // getter
    COORD getHead() const { return m_head; };

    // public interface
    void draw(GameConsole & console) const;
    void grow(COORD coord);
    bool hits(COORD coord) const;
    void move(Direction dir);

private:
    // private helper methods
    bool isBorderCollision(COORD coord);
};

 // helper function
 bool operator== (const COORD & coord1, const COORD & coord2);

 // =====================================================================================
 // End-of-File
 // =====================================================================================
