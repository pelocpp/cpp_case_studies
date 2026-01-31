// =====================================================================================
// Happy_Number_Cycle_Detection.cpp
// =====================================================================================

#include <cstddef>
#include <print>
#include <unordered_set>

// =====================================================================================

struct Node
{
    std::size_t m_value;
    Node*       m_next;
};

static Node* createLinkedListWithCycle()
{
    static Node node01{ 1 };
    static Node node02{ 2 };
    static Node node03{ 3 };
    static Node node04{ 4 };
    static Node node05{ 5 };
    static Node node06{ 6 };
    static Node node07{ 7 };
    static Node node08{ 8 };
    static Node node09{ 9 };

    node01.m_next = &node02;
    node02.m_next = &node03;
    node03.m_next = &node04;
    node04.m_next = &node05;
    node05.m_next = &node06;
    node06.m_next = &node07;
    node07.m_next = &node08;
    node08.m_next = &node09;
    node09.m_next = &node02;

    return &node01;
}

static Node* createLinkedListWithoutCycle()
{
    static Node node01{ 1 };
    static Node node02{ 2 };
    static Node node03{ 3 };
    static Node node04{ 4 };
    static Node node05{ 5 };

    node01.m_next = &node02;
    node02.m_next = &node03;
    node03.m_next = &node04;
    node04.m_next = &node05;
    node05.m_next = nullptr;

    return &node01;
}

static void printLinkedList(Node* root)
{
    struct Node* next = root;

    while (next != nullptr) {

        std::println("{}", next->m_value);
        next = next->m_next;
    }
}

// =====================================================================================

namespace LinkedList_CycleDetection_Using_HashTable {

    static bool detectCycle(Node* head)
    {
        std::unordered_set<Node*> cache;

        while (head != nullptr) {

            // node is already present in hash table, we've found a cycle
            if (cache.find(head) != cache.end()) {
                return true;
            }

            // we see the node for the first time,
            // insert node into the hash table
            cache.insert(head);

            head = head->m_next;
        }

        return false;
    }
}

// =====================================================================================

namespace LinkedList_CycleDetection_Floyd {

    static bool detectCycle(Node* root)
    {
        Node* slow = root;
        Node* fast = root;

        while (fast != nullptr && fast->m_next != nullptr) {

            slow = slow->m_next;
            fast = fast->m_next->m_next;

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
}

// =====================================================================================

static void test_cycle_detection_using_hash_table()
{
    Node* root = createLinkedListWithCycle();
    // printLinkedList(root);  // endless loop (!)
    bool isCyclic{ LinkedList_CycleDetection_Using_HashTable::detectCycle (root) };
    std::println("{}", isCyclic);

    root = createLinkedListWithoutCycle();
    printLinkedList(root);
    isCyclic = LinkedList_CycleDetection_Using_HashTable::detectCycle(root);
    std::println("{}", isCyclic);
}

static void test_cycle_detection_using_floyd()
{
    Node* root = createLinkedListWithCycle();
    // printLinkedList(root);  // endless loop (!)
    bool isCyclic{ LinkedList_CycleDetection_Floyd::detectCycle(root) };
    std::println("{}", isCyclic);

    root = createLinkedListWithoutCycle();
    printLinkedList(root);
    isCyclic = LinkedList_CycleDetection_Floyd::detectCycle(root);
    std::println("{}", isCyclic);
}

// =====================================================================================

void main_cycle_detection()
{
    test_cycle_detection_using_hash_table();
    test_cycle_detection_using_floyd();
}


// =====================================================================================
// End-of-File
// =====================================================================================

