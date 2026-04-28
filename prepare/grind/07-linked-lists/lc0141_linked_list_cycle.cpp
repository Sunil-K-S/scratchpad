/**
 * LeetCode 141 — Linked List Cycle
 * Difficulty: Easy
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given head of a linked list, determine if it contains a cycle.
 *   (A cycle means some node's next points to an earlier node.)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Floyd's Tortoise and Hare
 * ─────────────────────────────────────────────────────────────────────────────
 *   Use two pointers: slow (moves 1 step) and fast (moves 2 steps).
 *   If there is a cycle, fast will eventually lap slow and they will meet.
 *   If no cycle, fast reaches null first.
 *
 *   WHY they meet: In a cycle of length L, after slow enters the cycle,
 *   fast is some distance behind it and closes the gap by 1 per step.
 *   They must meet within L steps of slow entering the cycle.
 *
 *   Naive alternative: hash set of visited nodes → O(n) space.
 *   Floyd's: O(1) space.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (1→2→3→4→2 cycle)
 * ─────────────────────────────────────────────────────────────────────────────
 *   slow=1, fast=1
 *   Step 1: slow=2, fast=3
 *   Step 2: slow=3, fast=2  (fast wraps via 4→2)
 *   Step 3: slow=4, fast=4  ← MEET → cycle detected ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * EXTENSION: LC 142 — Find the cycle start
 * ─────────────────────────────────────────────────────────────────────────────
 *   Once slow and fast meet (inside the cycle):
 *   Reset one pointer to head. Advance both one step at a time.
 *   They meet again exactly at the cycle start.
 *   (Mathematical proof: distances work out so both travel equal distance
 *    to the entry point.)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n)
 *   SPACE: O(1)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Empty list (null)       → false
 *   Single node, no cycle   → false
 *   Single node, self-loop  → true

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Floyd's cycle detection (fast/slow pointer) finds cycles in any linked structure:
 *   - Deadlock detection in OS schedulers: model processes/resources as a graph;
 *     a cycle = deadlock. Floyd's algorithm detects it in O(n) with O(1) space.
 *   - Infinite loop detection in workflow engines: detect circular task dependencies
 *     in a DAG that was incorrectly configured.
 *   - Pollard's rho factorization: uses Floyd's cycle detection to factor large
 *     integers (used in cryptography).
 *   - Circular reference detection in garbage collectors: reference counting GC
 *     uses cycle detection to collect cyclic garbage.
 */

#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;         // advance 1 step
        fast = fast->next->next;   // advance 2 steps
        if (slow == fast) {
            return true;           // pointers met → cycle exists
        }
    }
    return false; // fast reached end → no cycle
}

int main() {
    // Build: 3 → 2 → 0 → -4 → (back to node at index 1)
    ListNode* n1 = new ListNode(3);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(0);
    ListNode* n4 = new ListNode(-4);
    n1->next = n2; n2->next = n3; n3->next = n4; n4->next = n2; // cycle
    std::cout << std::boolalpha << hasCycle(n1) << '\n'; // true

    // No cycle: 1 → 2
    ListNode* a = new ListNode(1);
    ListNode* b = new ListNode(2);
    a->next = b;
    std::cout << hasCycle(a) << '\n'; // false
    return 0;
}
