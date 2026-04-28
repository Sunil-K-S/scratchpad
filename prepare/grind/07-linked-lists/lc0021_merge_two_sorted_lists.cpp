/**
 * LeetCode 21 — Merge Two Sorted Lists
 * Difficulty: Easy
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Merge two sorted linked lists and return the merged list (also sorted).
 *
 *   Example: 1→2→4  and  1→3→4
 *   Output:  1→1→2→3→4→4
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Dummy head + comparison
 * ─────────────────────────────────────────────────────────────────────────────
 *   Use a dummy node as the start of the result list so we never need to
 *   special-case the head. Maintain a `tail` pointer to append efficiently.
 *
 *   At each step: pick the smaller head from the two lists, attach it to tail,
 *   advance that list's pointer. When one list is exhausted, attach the rest
 *   of the other (already sorted, so just link it directly).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (1→2→4  and  1→3→4)
 * ─────────────────────────────────────────────────────────────────────────────
 *   dummy→?  tail=dummy
 *   l1=1, l2=1: equal → take l1(1). tail→1. l1=2.
 *   l1=2, l2=1: l2<l1 → take l2(1). tail→1. l2=3.
 *   l1=2, l2=3: l1<l2 → take l1(2). tail→2. l1=4.
 *   l1=4, l2=3: l2<l1 → take l2(3). tail→3. l2=4.
 *   l1=4, l2=4: equal → take l1(4). tail→4. l1=null.
 *   l1=null: attach rest of l2 (4). tail→4.
 *   Result: 1→1→2→3→4→4 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(m + n) — visit each node exactly once
 *   SPACE: O(1) — no new nodes created (reuse existing nodes)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Either list empty     → return the other list
 *   One element each      → compare and link
 *   Identical lists       → interleave (works correctly)
 *
 * INTERVIEW TIP:
 *   Always mention the dummy-head trick — it eliminates a special case for
 *   initializing the result head. This pattern appears in many list problems.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Merging two sorted sequences is a core primitive in many systems:
 *   - Database external merge sort: the final merge phase of sorting data larger
 *     than RAM repeatedly merges pairs of sorted runs.
 *   - Social feed aggregation: merge two sorted-by-time activity streams (e.g.,
 *     friend posts + page posts) into a unified timeline.
 *   - DNS zone file merging: merge two authoritative sorted zone files during
 *     incremental transfer (AXFR/IXFR).
 *   - Merge sort (divide and conquer): the merge step is literally this algorithm.
 */

#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);       // sentinel: no special case for result head
    ListNode* tail = &dummy;

    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val <= l2->val) {
            tail->next = l1;  // attach smaller node
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;    // advance tail
    }
    // At most one list still has nodes — attach the rest directly
    tail->next = (l1 != nullptr) ? l1 : l2;
    return dummy.next;
}

// ── Helpers ──────────────────────────────────────────────────────────────────
ListNode* makeList(std::initializer_list<int> vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) { tail->next = new ListNode(v); tail = tail->next; }
    return dummy.next;
}
void printList(ListNode* h) {
    while (h) { std::cout << h->val; if (h->next) std::cout << "→"; h = h->next; }
    std::cout << "→null\n";
}

int main() {
    printList(mergeTwoLists(makeList({1,2,4}), makeList({1,3,4}))); // 1→1→2→3→4→4
    printList(mergeTwoLists(nullptr, makeList({0})));               // 0
    printList(mergeTwoLists(nullptr, nullptr));                     // null
    return 0;
}
