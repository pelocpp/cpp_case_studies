// =====================================================================================
// Tetris Priority Queue Ex
// =====================================================================================

//template <typename T, typename Allocator = std::allocator<T>>
//class TetrisQueueEx : public std::deque<T, Allocator>
//{
//public:
//    int count();
//};
//
//template <typename T, typename Allocator>
//int TetrisQueueEx<T, Allocator>::count() {
//    return std::deque<T, Allocator>::size();
//}

// =====================================================================================
// Tetris Priority Queue
// =====================================================================================

//template <
//    typename T,
//    typename Container = std::vector<T>,
//    typename Compare = std::less<typename Container::value_type>
//>
//class TetrisQueue : public std::priority_queue<T, Container, Compare>
//{
//public:
//    using const_iterator = 
//        typename std::priority_queue <T, Container, Compare>::container_type::const_iterator;
//
//    // iterator interface
//    const_iterator begin();
//    const_iterator end();
//
//    // public interface
//    bool contains(const T&);
//    void dump();
//    int count();
//    bool anyHighPrioAction();
//    bool anyLowPrioAction();
//};

// =====================================================================================
// implementation

//template <typename T, typename Container, typename Compare>
//typename TetrisQueue<T, Container, Compare>::const_iterator TetrisQueue<T, Container, Compare>::begin() {
//    return this->c.cbegin();
//}
//
//template <typename T, typename Container, typename Compare>
//typename TetrisQueue<T, Container, Compare>::const_iterator TetrisQueue<T, Container, Compare>::end() {
//    return this->c.cend();
//}
//
//template <typename T, typename Container, typename Compare>
//bool TetrisQueue<T, Container, Compare>::contains(const T& elem) {
//    auto first = this->c.cbegin();
//    auto last = this->c.cend();
//    while (first != last) {
//        if (*first == elem) {
//            return true;
//        }
//        ++first;
//    }
//
//    return false;
//}
//
//template <typename T, typename Container, typename Compare>
//int TetrisQueue<T, Container, Compare>::count() {
//    return this->c.size();
//}

//template <typename T, typename Container, typename Compare>
//bool TetrisQueue<T, Container, Compare>::anyHighPrioAction() {
//    auto first = this->c.cbegin();
//    auto last = this->c.cend();
//    while (first != last) {
//        auto [prio, action] = *first;
//        if (prio == TetrisActionPrio::High)
//            return true;
//        ++first;
//    }
//
//    return false;
//}

//template <typename T, typename Container, typename Compare>
//bool TetrisQueue<T, Container, Compare>::anyLowPrioAction() {
//    auto first = this->c.cbegin();
//    auto last = this->c.cend();
//    while (first != last) {
//        auto [prio, action] = *first;
//        if (prio == TetrisActionPrio::Normal || prio == TetrisActionPrio::Low)
//            return true;
//        ++first;
//    }
//
//    return false;
//}

//template <typename T, typename Container, typename Compare>
//void TetrisQueue<T, Container, Compare>::dump() {
//    std::ostringstream oss;
//    oss << "=========================================\n";
//    oss << "Tetris Actions Queue [" << this->c.size() << "]:\n";
//    std::for_each(
//        std::begin(this->c),
//        std::end(this->c),
//        [&](const TetrisActionPair& pair) {
//            oss << pair << '\n';
//        }
//    );
//    oss << "-----------------------------------------\n";
//    ::OutputDebugString(oss.str().data());
//}

// =====================================================================================
// End-of-File
// =====================================================================================


// =====================================================================================
// TetrisAction: enums and miscellaneous functions
// =====================================================================================

#pragma once


//enum class TetrisActionPrio {
//    Low,
//    Normal,
//    High
//};
//
//using TetrisActionPair = std::pair<TetrisActionPrio, TetrisAction>;
//
//extern std::ostream& operator<< (std::ostream&, const TetrisActionPair&); 
//extern bool operator== (const TetrisActionPair&, const TetrisActionPair&);

// =====================================================================================
// central location to provide priority to tetris actions

//template <TetrisAction action>
//TetrisActionPair makeAction() {
//    if constexpr (action == TetrisAction::AtTop) {
//        return std::make_pair(TetrisActionPrio::Normal, TetrisAction::AtTop);
//    }
//    if constexpr (action == TetrisAction::WayDown) {
//        return std::make_pair(TetrisActionPrio::Normal, TetrisAction::WayDown);
//    }
//    if constexpr (action == TetrisAction::DoLeft) {
//        return std::make_pair(TetrisActionPrio::High, TetrisAction::DoLeft);
//    }
//    if constexpr (action == TetrisAction::DoRight) {
//        return std::make_pair(TetrisActionPrio::High, TetrisAction::DoRight);
//    }
//    if constexpr (action == TetrisAction::DoRotate) {
//        return std::make_pair(TetrisActionPrio::High, TetrisAction::DoRotate);
//    }
//    if constexpr (action == TetrisAction::AllWayDown) {
//        return std::make_pair(TetrisActionPrio::High, TetrisAction::AllWayDown);
//    }
//    if constexpr (action == TetrisAction::AtBottom) {
//        return std::make_pair(TetrisActionPrio::Normal, TetrisAction::AtBottom);
//    }
//    if constexpr (action == TetrisAction::GameOver) {
//        return std::make_pair(TetrisActionPrio::High, TetrisAction::GameOver);
//    }

    //if constexpr (action == TetrisAction::AtTop) {
    //    return std::make_pair(TetrisActionPrio::Normal, TetrisAction::AtTop);
    //}
    //if constexpr (action == TetrisAction::WayDown) {
    //    return std::make_pair(TetrisActionPrio::Normal, TetrisAction::WayDown);
    //}
    //if constexpr (action == TetrisAction::DoLeft) {
    //    return std::make_pair(TetrisActionPrio::Low, TetrisAction::DoLeft);
    //}
    //if constexpr (action == TetrisAction::DoRight) {
    //    return std::make_pair(TetrisActionPrio::Low, TetrisAction::DoRight);
    //}
    //if constexpr (action == TetrisAction::DoRotate) {
    //    return std::make_pair(TetrisActionPrio::Low, TetrisAction::DoRotate);
    //}
    //if constexpr (action == TetrisAction::AllWayDown) {
    //    return std::make_pair(TetrisActionPrio::Low, TetrisAction::AllWayDown);
    //}
    //if constexpr (action == TetrisAction::AtBottom) {
    //    return std::make_pair(TetrisActionPrio::Normal, TetrisAction::AtBottom);
    //}
    //if constexpr (action == TetrisAction::GameOver) {
    //    return std::make_pair(TetrisActionPrio::High, TetrisAction::GameOver);
    //}
//}

// =====================================================================================
// End-of-File
// =====================================================================================


// =====================================================================================
// TetrisAction: enums and miscellaneous functions
// =====================================================================================



// =====================================================================================
// maps just for dumping tetris actions

//std::map<TetrisAction, std::string> tetrisActionIdentifiers{
//    {  TetrisAction::None,       "None"       },
//    {  TetrisAction::AtTop,      "AtTop"      },
//    {  TetrisAction::WayDown,    "WayDown"    },
//    {  TetrisAction::DoLeft,     "DoLeft"     },
//    {  TetrisAction::DoRight,    "DoRight"    },
//    {  TetrisAction::DoRotate,   "DoRotate"   },
//    {  TetrisAction::AllWayDown, "AllWayDown" },
//    {  TetrisAction::AtBottom,   "AtBottom"   },
//    {  TetrisAction::GameOver,   "GameOver"   }
//};
//
//std::map<TetrisActionPrio, std::string> tetrisActionPrioIdentifiers{
//    {  TetrisActionPrio::Low,    "Low"    },
//    {  TetrisActionPrio::Normal, "Normal" },
//    {  TetrisActionPrio::High,   "High"   }
//};
//
//bool operator== (const TetrisActionPair& lhs, const TetrisActionPair& rhs) {
//    return lhs.first == rhs.first && lhs.second == rhs.second;
//}
//
//std::ostream& operator<< (std::ostream& os, const TetrisActionPair& pair) {
//    os 
//        << "Prio: " << tetrisActionPrioIdentifiers[pair.first] 
//        << ", Action: " << tetrisActionIdentifiers[pair.second];
//    return os;
//}

// =====================================================================================
// End-of-File
// =====================================================================================