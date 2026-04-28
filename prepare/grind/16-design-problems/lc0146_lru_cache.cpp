/**
 * LeetCode 146 — LRU Cache
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Implement LRU (Least Recently Used) cache with capacity c:
 *   - get(key): return value if exists, else -1. Marks as recently used.
 *   - put(key, val): insert/update. If at capacity, evict LRU item first.
 *
 *   Both operations must be O(1).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: HashMap + Doubly Linked List
 * ─────────────────────────────────────────────────────────────────────────────
 *   PROBLEM: We need O(1) access (HashMap) AND O(1) order maintenance (DLL).
 *
 *   - HashMap: key → DLL node* (O(1) lookup)
 *   - DLL: maintains order (MRU at head, LRU at tail)
 *   - SENTINELS: dummy head and dummy tail nodes eliminate all null checks
 *
 *   OPERATIONS:
 *   get(key):
 *     - Not found → return -1
 *     - Found → move node to front (MRU), return value
 *
 *   put(key, val):
 *     - Key exists → update value, move to front
 *     - Key new, capacity full → remove tail.prev (LRU), remove from map
 *     - Insert at front, add to map
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (capacity=2)
 * ─────────────────────────────────────────────────────────────────────────────
 *   put(1,1): map={1:n1}, DLL: H↔1↔T
 *   put(2,2): map={1:n1,2:n2}, DLL: H↔2↔1↔T
 *   get(1):   move 1 to front → DLL: H↔1↔2↔T, return 1
 *   put(3,3): capacity full, evict LRU=2 (tail.prev)
 *             DLL: H↔3↔1↔T, map={1:n1,3:n3}
 *   get(2):   key 2 not found → return -1
 *   get(3):   move 3 to front (already front), return 3
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   get/put: O(1) — all operations are pointer manipulation + hash lookup
 *   SPACE:   O(capacity)
 *
 * CORNER CASES:
 *   put same key twice → update, no eviction
 *   get on key just put → should not evict it even if LRU

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   LRU cache is one of the most widely deployed algorithms in systems software:
 *   - Browser cache: evict the least recently accessed web resources when the
 *     cache fills up — Chrome and Firefox implement LRU or variants.
 *   - CPU L1/L2/L3 cache replacement: hardware LRU (approximated) decides which
 *     cache line to evict on a miss.
 *   - Redis maxmemory-policy allkeys-lru: Redis evicts the LRU key when memory
 *     is exhausted — the eviction logic is this exact data structure.
 *   - Database buffer pool: InnoDB (MySQL) uses a modified LRU list to manage
 *     which disk pages stay in memory.
 */

#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
    int key, val;
    Node *prev, *next;
    Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
    int capacity;
    unordered_map<int, Node*> cache; // key → node*
    Node* head; // dummy head (MRU side)
    Node* tail; // dummy tail (LRU side)

    void remove(Node* n) {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }
    void insertFront(Node* n) {
        n->next = head->next;
        n->prev = head;
        head->next->prev = n;
        head->next = n;
    }
public:
    LRUCache(int cap) : capacity(cap) {
        head = new Node(0, 0); // dummy head
        tail = new Node(0, 0); // dummy tail
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) return -1;
        Node* n = it->second;
        remove(n);
        insertFront(n); // mark as recently used
        return n->val;
    }

    void put(int key, int value) {
        if (cache.count(key)) {
            Node* n = cache[key];
            n->val = value;
            remove(n);
            insertFront(n);
        } else {
            if (static_cast<int>(cache.size()) == capacity) {
                Node* lru = tail->prev; // least recently used
                remove(lru);
                cache.erase(lru->key);
                delete lru;
            }
            Node* n = new Node(key, value);
            insertFront(n);
            cache[key] = n;
        }
    }
};

int main() {
    LRUCache lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    std::cout << lru.get(1) << '\n'; // 1
    lru.put(3, 3);                   // evict key=2
    std::cout << lru.get(2) << '\n'; // -1
    lru.put(4, 4);                   // evict key=1
    std::cout << lru.get(1) << '\n'; // -1
    std::cout << lru.get(3) << '\n'; // 3
    std::cout << lru.get(4) << '\n'; // 4
    return 0;
}
