/**
 * LeetCode 23 — Merge K Sorted Lists
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Merge k sorted linked lists and return as one sorted list.
 *
 *   Example: lists=[[1,4,5],[1,3,4],[2,6]] → [1,1,2,3,4,4,5,6]
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Min-heap over the k list heads
 * ─────────────────────────────────────────────────────────────────────────────
 *   BRUTE FORCE: Collect all values, sort, rebuild → O(N log N). Works but wasteful.
 *
 *   OPTIMAL: We don't need to see all elements at once.
 *   At any moment, the next element in the merged list must be the MINIMUM of
 *   the current fronts of all k lists.
 *
 *   Use a min-heap storing (value, node*) for the current head of each list.
 *   - Pop min: that's the next output node.
 *   - If it has a next, push next onto heap.
 *   - Repeat until heap is empty.
 *
 *   Heap always has at most k elements → O(log k) per operation.
 *   Total N output nodes → O(N log k).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (lists=[[1,4],[1,3],[2]])
 * ─────────────────────────────────────────────────────────────────────────────
 *   Init heap: {(1,L0),(1,L1),(2,L2)}
 *   Pop (1,L0): output 1 → push L0.next=(4): heap={(1,L1),(2,L2),(4,L0)}
 *   Pop (1,L1): output 1 → push L1.next=(3): heap={(2,L2),(3,L1),(4,L0)}
 *   Pop (2,L2): output 2 → L2.next=null:     heap={(3,L1),(4,L0)}
 *   Pop (3,L1): output 3 → L1.next=null:     heap={(4,L0)}
 *   Pop (4,L0): output 4 → L0.next=null:     heap={}
 *   Result: 1→1→2→3→4
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(N log k) — N total nodes, heap size at most k
 *   SPACE: O(k) — heap stores at most k entries
 *
 * CORNER CASES:
 *   Empty lists array → null
 *   Lists with null pointers → skip them at init
 *   All lists have 1 element → still O(N log k)

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   K-way merge is a foundational algorithm in distributed data processing:
 *   - External merge sort (databases, Hadoop): the final merge phase reads k
 *     sorted temporary files simultaneously using a heap — this exact algorithm.
 *   - Log aggregation: merge k chronologically sorted log streams from k servers
 *     into one unified timeline (used in Splunk, ELK stack ingestion pipelines).
 *   - Multi-source feed merging: merge sorted activity feeds from k data sources
 *     (social graph edges, ads, recommendations) in a unified news feed.
 *   - DNA sequencing: merge k sorted read alignments from k parallel sequencers.
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    // Min-heap: (value, pointer)
    using P = pair<int, ListNode*>;
    priority_queue<P, vector<P>, greater<P>> heap;

    for (ListNode* head : lists) {
        if (head) heap.push({head->val, head});
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!heap.empty()) {
        auto [val, node] = heap.top(); heap.pop();
        tail->next = node;
        tail = tail->next;
        if (node->next) heap.push({node->next->val, node->next});
    }
    return dummy.next;
}

int main() {
    // Build [1->4], [1->3->4], [2->6]
    ListNode* l1 = new ListNode(1); l1->next = new ListNode(4);
    ListNode* l2 = new ListNode(1); l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    ListNode* l3 = new ListNode(2); l3->next = new ListNode(6);

    vector<ListNode*> lists = {l1, l2, l3};
    ListNode* head = mergeKLists(lists);
    for (ListNode* n = head; n; n = n->next)
        std::cout << n->val << (n->next ? "->" : "\n");
    // 1->1->2->3->4->4->6
    return 0;
}
