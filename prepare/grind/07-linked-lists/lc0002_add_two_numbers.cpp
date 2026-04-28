/**
 * LeetCode 2 — Add Two Numbers
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Two non-empty linked lists store non-negative integers in REVERSE order
 *   (least significant digit first). Add the two numbers and return the sum
 *   as a linked list (also in reverse order).
 *
 *   Example: (2→4→3) + (5→6→4)  →  342 + 465 = 807  →  7→0→8
 *
 * CONSTRAINTS:
 *   No leading zeros (except the number 0 itself).
 *   1 <= length <= 100, 0 <= node.val <= 9
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Simulate grade-school addition with carry
 * ─────────────────────────────────────────────────────────────────────────────
 *   Walk both lists simultaneously. At each digit position:
 *     sum = l1->val + l2->val + carry
 *     new digit = sum % 10
 *     carry = sum / 10
 *   The stored digits are already in the right order (LSB first) so we just
 *   walk left to right and produce the result list in the same direction.
 *
 *   Continue while either list has nodes OR carry != 0.
 *   Missing digits from the shorter list count as 0.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  ((2→4→3) + (5→6→4))
 * ─────────────────────────────────────────────────────────────────────────────
 *   carry=0
 *   Pos 0: 2+5+0=7,  digit=7, carry=0  → result: 7
 *   Pos 1: 4+6+0=10, digit=0, carry=1  → result: 7→0
 *   Pos 2: 3+4+1=8,  digit=8, carry=0  → result: 7→0→8
 *   Both null, carry=0: done.
 *   Answer: 7→0→8  (represents 807) ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(max(m, n)) — m, n = lengths of the two lists
 *   SPACE: O(max(m, n) + 1) — result list has at most max(m,n)+1 nodes
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Different lengths:   [1,8] + [0] = 1+80? No — reversed, so [1,8]=81, [0]=0
 *                         81+0=81 → [1,8]. Handled by treating missing as 0.
 *   Final carry:         [5] + [5] = 10 → [0,1]. Loop condition includes carry.
 *   Both single zeros:   [0] + [0] = [0].

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Digit-by-digit arithmetic on linked representations is used in big number systems:
 *   - Arbitrary-precision arithmetic libraries (Python int, Java BigInteger,
 *     OpenSSL BN): store digits as linked arrays and add with carry propagation.
 *   - Financial systems: monetary calculations that must be exact (no floating-point
 *     rounding) use fixed-point or big-integer representations.
 *   - Cryptography: RSA key operations work on integers hundreds of digits long;
 *     the underlying add/multiply routines follow this carry-propagation pattern.
 */

#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    int carry = 0;

    while (l1 != nullptr || l2 != nullptr || carry != 0) {
        int sum = carry;
        if (l1 != nullptr) { sum += l1->val; l1 = l1->next; }
        if (l2 != nullptr) { sum += l2->val; l2 = l2->next; }
        carry = sum / 10;                      // will be 0 or 1
        tail->next = new ListNode(sum % 10);   // current digit
        tail = tail->next;
    }
    return dummy.next;
}

// ── Helpers ──────────────────────────────────────────────────────────────────
ListNode* makeList(std::initializer_list<int> v) {
    ListNode d(0); ListNode* t = &d;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return d.next;
}
void printList(ListNode* h) {
    while (h) { std::cout << h->val; if (h->next) std::cout << "→"; h = h->next; }
    std::cout << '\n';
}

int main() {
    // 342 + 465 = 807
    printList(addTwoNumbers(makeList({2,4,3}), makeList({5,6,4}))); // 7→0→8
    // 0 + 0 = 0
    printList(addTwoNumbers(makeList({0}), makeList({0})));          // 0
    // 999 + 1 = 1000
    printList(addTwoNumbers(makeList({9,9,9}), makeList({1})));      // 0→0→0→1
    return 0;
}
