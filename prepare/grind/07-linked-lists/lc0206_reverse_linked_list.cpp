/**
 * LeetCode 206 — Reverse Linked List
 * Difficulty: Easy
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given the head of a singly linked list, reverse it and return the new head.
 *
 *   Example: 1 → 2 → 3 → 4 → 5 → null
 *   Output:  5 → 4 → 3 → 2 → 1 → null
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Three-pointer iterative reversal
 * ─────────────────────────────────────────────────────────────────────────────
 *   To reverse a link A → B → C:
 *   Before changing A's next, save B (otherwise you lose the rest of the list).
 *   Then point A back to whatever came before it.
 *
 *   Use three pointers: prev, curr, next_node.
 *   At each step:
 *     1. Save next_node = curr->next       (save the rest)
 *     2. curr->next = prev                 (reverse the link)
 *     3. prev = curr                       (advance prev)
 *     4. curr = next_node                  (advance curr)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (1 → 2 → 3 → null)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Start: prev=null, curr=1
 *
 *   Iter 1: next=2, 1→null, prev=1, curr=2.    List state: null←1  2→3
 *   Iter 2: next=3, 2→1,    prev=2, curr=3.    List state: null←1←2  3
 *   Iter 3: next=null, 3→2, prev=3, curr=null. List state: null←1←2←3
 *
 *   curr==null: stop. Return prev=3. ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * RECURSIVE VERSION (know both)
 * ─────────────────────────────────────────────────────────────────────────────
 *   reverseList(head):
 *     if head == null or head->next == null: return head  (base case)
 *     new_head = reverseList(head->next)   // reverse the tail
 *     head->next->next = head              // make next node point back
 *     head->next = null                    // cut original forward link
 *     return new_head
 *
 *   Recursive space: O(n) call stack. Iterative: O(1). Prefer iterative.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — visit each node once
 *   SPACE: O(1) iterative / O(n) recursive (call stack)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   null (empty list)   → return null
 *   single node [1]     → return same node (no links to reverse)
 *   two nodes [1,2]     → 2→1→null

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   In-place pointer reversal is the basis of undo/redo and history traversal:
 *   - Browser history: reversing the forward/backward navigation stack when
 *     the user navigates to a new page (forward history is invalidated).
 *   - Undo/redo in editors: reversing the command linked list for multi-level undo.
 *   - Version control: reversing a patch list to reconstruct an earlier snapshot.
 *   - Network packet processing: reversing a chain of protocol headers during
 *     decapsulation in a software-defined networking (SDN) pipeline.
 */

#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

// ── Iterative (preferred) ────────────────────────────────────────────────────
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr != nullptr) {
        ListNode* next_node = curr->next; // 1. save rest of list
        curr->next = prev;               // 2. reverse the link
        prev = curr;                     // 3. advance prev
        curr = next_node;                // 4. advance curr
    }
    return prev; // prev is now the new head
}

// ── Helpers for testing ──────────────────────────────────────────────────────
ListNode* makeList(std::initializer_list<int> vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

void printList(ListNode* head) {
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << " → ";
        head = head->next;
    }
    std::cout << " → null\n";
}

int main() {
    ListNode* l1 = makeList({1, 2, 3, 4, 5});
    printList(reverseList(l1)); // 5 → 4 → 3 → 2 → 1 → null

    ListNode* l2 = makeList({1, 2});
    printList(reverseList(l2)); // 2 → 1 → null

    printList(reverseList(nullptr)); // → null
    return 0;
}
