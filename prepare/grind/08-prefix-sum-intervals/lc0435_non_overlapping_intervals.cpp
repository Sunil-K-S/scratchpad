/**
 * LeetCode 435 — Non-overlapping Intervals
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given intervals, find the minimum number to REMOVE so that the rest are
 *   non-overlapping.
 *
 *   Example: [[1,2],[2,3],[3,4],[1,3]]
 *   Output: 1  (remove [1,3])
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Greedy — keep the interval with the earliest end time
 * ─────────────────────────────────────────────────────────────────────────────
 *   This is equivalent to: find the MAXIMUM number of non-overlapping intervals
 *   (Activity Selection Problem), then answer = n - max_kept.
 *
 *   Greedy rule: Among all intervals that don't conflict with previously kept
 *   ones, always pick the one with the SMALLEST end time.
 *   WHY: Smaller end time leaves the most room for future intervals.
 *
 *   Algorithm:
 *   1. Sort by END time.
 *   2. Keep a running `last_end` (end of the last kept interval).
 *   3. For each interval:
 *      - If its start >= last_end → no conflict, keep it, update last_end.
 *      - Else → conflict, remove it (increment count).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  ([[1,2],[2,3],[3,4],[1,3]] sorted by end)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Sorted by end: [[1,2],[2,3],[1,3],[3,4]]
 *   last_end = INT_MIN, remove = 0
 *
 *   [1,2]: 1 >= -inf → keep. last_end=2.
 *   [2,3]: 2 >= 2   → keep. last_end=3.
 *   [1,3]: 1 < 3    → conflict! remove++. (remove=1)
 *   [3,4]: 3 >= 3   → keep. last_end=4.
 *   Answer: 1 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n log n) — sort dominates
 *   SPACE: O(1)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Single interval          → 0 removals
 *   All overlapping          → keep 1, remove n-1
 *   Touching (end == start)  → NOT overlapping (e.g., [1,2] and [2,3] are fine)

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Minimum removals to eliminate overlap = maximum non-overlapping scheduling:
 *   - Meeting room scheduling: select the maximum number of meetings that can be
 *     held in one conference room (Activity Selection Problem).
 *   - CPU / GPU kernel scheduling: schedule the maximum number of tasks on a
 *     single core without conflicts.
 *   - Video streaming: select the maximum non-overlapping set of ad slots to
 *     insert into a video without overlapping scene transitions.
 *   - Network packet scheduling: select maximum non-conflicting transmission windows.
 */

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    // Sort by end time — greedy activity selection
    sort(intervals.begin(), intervals.end(),
         [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });

    int removals = 0;
    int last_end = INT_MIN;

    for (const auto& iv : intervals) {
        if (iv[0] >= last_end) {
            last_end = iv[1]; // keep this interval
        } else {
            ++removals;       // conflict: remove this interval
        }
    }
    return removals;
}

int main() {
    vector<vector<int>> iv1 = {{1,2},{2,3},{3,4},{1,3}};
    std::cout << eraseOverlapIntervals(iv1) << '\n'; // 1

    vector<vector<int>> iv2 = {{1,2},{1,2},{1,2}};
    std::cout << eraseOverlapIntervals(iv2) << '\n'; // 2

    vector<vector<int>> iv3 = {{1,2},{2,3}};
    std::cout << eraseOverlapIntervals(iv3) << '\n'; // 0
    return 0;
}
