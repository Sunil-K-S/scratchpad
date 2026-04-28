/**
 * LeetCode 215 — Kth Largest Element in an Array
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return the kth largest element in an unsorted array (not kth distinct).
 *
 *   Example: nums=[3,2,1,5,6,4], k=2 → 5
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * TWO APPROACHES
 * ─────────────────────────────────────────────────────────────────────────────
 *
 * APPROACH 1: Min-heap of size k — O(n log k)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Maintain a min-heap of the k largest elements seen so far.
 *   - If heap size < k: push element.
 *   - If element > heap.top(): pop min, push element.
 *   At the end, heap.top() = kth largest.
 *
 *   WHY: The heap always holds the k largest seen. Its minimum is the kth largest.
 *   GOOD FOR: streaming data (don't need all data at once), or n >> k.
 *
 * APPROACH 2: QuickSelect — O(n) average
 * ─────────────────────────────────────────────────────────────────────────────
 *   Like quicksort but only recurse into ONE side.
 *   kth largest = (n-k)th smallest (0-indexed).
 *   Partition around a pivot; if pivot lands at target index → done.
 *
 *   Average O(n), worst O(n^2) (use random pivot to avoid).
 *   O(1) extra space (in-place). Better constant than heap approach.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY COMPARISON
 * ─────────────────────────────────────────────────────────────────────────────
 *   Min-heap:    O(n log k) time, O(k) space
 *   QuickSelect: O(n) avg time, O(1) space (O(n^2) worst)
 *   Full sort:   O(n log n) time — never the right answer here
 *
 * CORNER CASES:
 *   k=1 → maximum element
 *   k=n → minimum element
 *   Duplicates handled correctly by both approaches

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Finding the kth largest without full sort is used in analytics and streaming:
 *   - Leaderboards: show the top-k players in an online game without sorting
 *     all millions of players (min-heap of size k is the standard approach).
 *   - Recommendation systems: find the top-k most relevant items for a user
 *     from a scored candidate set (used in Netflix, Spotify recommendation).
 *   - Database ORDER BY ... LIMIT k: query engines use a heap of size k
 *     internally rather than sorting all rows.
 *   - Stream processing (Kafka Streams, Flink): find the kth highest metric
 *     value over a sliding window of incoming events.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ── Approach 1: Min-heap (preferred in interviews for clarity) ────────────────
int findKthLargestHeap(const vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> min_heap; // min at top
    for (int x : nums) {
        min_heap.push(x);
        if (static_cast<int>(min_heap.size()) > k) {
            min_heap.pop(); // evict the smallest (not in top-k)
        }
    }
    return min_heap.top(); // kth largest
}

// ── Approach 2: QuickSelect ───────────────────────────────────────────────────
int quickSelect(vector<int>& nums, int lo, int hi, int target_idx) {
    if (lo == hi) return nums[lo];

    // Random pivot for average O(n)
    int pivot_idx = lo + rand() % (hi - lo + 1);
    swap(nums[pivot_idx], nums[hi]);
    int pivot = nums[hi];
    int i = lo;
    for (int j = lo; j < hi; ++j) {
        if (nums[j] <= pivot) swap(nums[i++], nums[j]);
    }
    swap(nums[i], nums[hi]); // place pivot

    if (i == target_idx) return nums[i];
    if (i < target_idx)  return quickSelect(nums, i + 1, hi, target_idx);
    return quickSelect(nums, lo, i - 1, target_idx);
}

int findKthLargest(vector<int> nums, int k) {
    int n = static_cast<int>(nums.size());
    return quickSelect(nums, 0, n - 1, n - k); // kth largest = (n-k)th smallest
}

int main() {
    std::cout << findKthLargestHeap({3,2,1,5,6,4}, 2) << '\n'; // 5
    std::cout << findKthLargest({3,2,3,1,2,4,5,5,6}, 4) << '\n'; // 4
    return 0;
}
