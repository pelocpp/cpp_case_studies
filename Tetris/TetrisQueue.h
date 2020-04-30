// =====================================================================================
// Tetris Priority Queue
// =====================================================================================

template <
    typename T,
    typename Container = std::vector<T>,
    typename Compare = std::less<typename Container::value_type>
>
class TetrisQueue : public std::priority_queue<T, Container, Compare>
{
public:
    using const_iterator = 
        typename std::priority_queue <T, Container, Compare>::container_type::const_iterator;

    // iterator interface
    const_iterator begin();
    const_iterator end();

    // public interface
    bool contains(const T&);
    void dump();
    int count();
    bool anyHighPrioAction();
    bool anyLowPrioAction();
};

// =====================================================================================
// implementation

template <typename T, typename Container, typename Compare>
typename TetrisQueue<T, Container, Compare>::const_iterator TetrisQueue<T, Container, Compare>::begin() {
    return this->c.cbegin();
}

template <typename T, typename Container, typename Compare>
typename TetrisQueue<T, Container, Compare>::const_iterator TetrisQueue<T, Container, Compare>::end() {
    return this->c.cend();
}

template <typename T, typename Container, typename Compare>
bool TetrisQueue<T, Container, Compare>::contains(const T& elem) {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
        if (*first == elem) {
            return true;
        }
        ++first;
    }

    return false;
}

template <typename T, typename Container, typename Compare>
int TetrisQueue<T, Container, Compare>::count() {
    return this->c.size();
}

template <typename T, typename Container, typename Compare>
bool TetrisQueue<T, Container, Compare>::anyHighPrioAction() {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
        auto [prio, action] = *first;
        if (prio == TetrisActionPrio::High)
            return true;
        ++first;
    }

    return false;
}

template <typename T, typename Container, typename Compare>
bool TetrisQueue<T, Container, Compare>::anyLowPrioAction() {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
        auto [prio, action] = *first;
        if (prio == TetrisActionPrio::Normal || prio == TetrisActionPrio::Low)
            return true;
        ++first;
    }

    return false;
}

template <typename T, typename Container, typename Compare>
void TetrisQueue<T, Container, Compare>::dump() {
    std::ostringstream oss;
    oss << "=========================================\n";
    oss << "Tetris Actions Queue [" << this->c.size() << "]:\n";
    std::for_each(
        std::begin(this->c),
        std::end(this->c),
        [&](const TetrisActionPair& pair) {
            oss << pair << '\n';
        }
    );
    oss << "-----------------------------------------\n";
    ::OutputDebugString(oss.str().data());
}

// =====================================================================================
// End-of-File
// =====================================================================================