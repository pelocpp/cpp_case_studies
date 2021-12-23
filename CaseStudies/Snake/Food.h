// =====================================================================================
// Food.h
// =====================================================================================

class Food
{
private:
    COORD m_coord;
    std::random_device m_device;

public:
    // c'tor
    Food();  

    // getter
    COORD getPosition() const { return m_coord; };

    // public interface
    void createCollisionFree(const Snake& snake);
    void draw(GameConsole& console);
};

// =====================================================================================
// End-of-File
// =====================================================================================
