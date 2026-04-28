/**
 * LeetCode 56 — Merge Intervals
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given an array of intervals [start, end], merge all overlapping intervals.
 *
 *   Example: [[1,3],[2,6],[8,10],[15,18]]
 *   Output:  [[1,6],[8,10],[15,18]]
 *   (Because [1,3] and [2,6] overlap → merge to [1,6])
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Sort by start, then greedy merge
 * ─────────────────────────────────────────────────────────────────────────────
 *   After sorting by start time, overlapping intervals are always adjacent.
 *   No need to check intervals far away.
 *
 *   Two intervals [a,b] and [c,d] (with a <= c) overlap iff c <= b.
 *   If they overlap, merge to [a, max(b,d)].
 *
 *   Algorithm:
 *   1. Sort intervals by start.
 *   2. Push first interval to result.
 *   3. For each subsequent interval:
 *      - If it overlaps with result.back() → extend result.back().end if needed.
 *      - Else → push as new interval.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  ([[1,3],[2,6],[8,10],[15,18]])
 * ─────────────────────────────────────────────────────────────────────────────
 *   After sort (already sorted): [[1,3],[2,6],[8,10],[15,18]]
 *
 *   result = [[1,3]]
 *   Process [2,6]: 2 <= 3 → overlap. Extend: result=[[1,6]]
 *   Process [8,10]: 8 > 6 → no overlap. Push: result=[[1,6],[8,10]]
 *   Process [15,18]: 15 > 10 → no overlap. Push: result=[[1,6],[8,10],[15,18]]
 *   Answer: [[1,6],[8,10],[15,18]] ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n log n) — dominated by sort; merge pass is O(n)
 *   SPACE: O(n) — output array (sort uses O(log n) stack)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Single interval          → return as-is
 *   All intervals overlap    → one big merged interval
 *   No intervals overlap     → return sorted input unchanged
 *   [1,4],[2,3]: [2,3] fully inside [1,4] → max(end)=4, result=[1,4]
 *
 * INTERVIEW TIP:
 *   "Sort first" is the unlock. Without it you'd need O(n^2) comparison.
 *   This exact pattern appears in LC 435 (non-overlapping) and LC 57 (insert).

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Interval merging is fundamental in calendar and network systems:
 *   - Calendar / scheduling apps (Google Calendar, Outlook): merge overlapping
 *     meeting blocks to show busy spans and find free time slots.
 *   - IP address management (IPAM): consolidate overlapping CIDR ranges into
 *     the minimal set of non-overlapping ranges for firewall rules.
 *   - Code coverage tools: merge overlapping source ranges reported by different
 *     test runs to get the total covered region.
 *   - Database vacuum / defrag: merge adjacent free page extents into one block.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    // Sort by start time
    sort(intervals.begin(), intervals.end(),
         [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

    vector<vector<int>> result;
    result.push_back(intervals[0]);

    for (int i = 1; i < static_cast<int>(intervals.size()); ++i) {
        auto& last = result.back();
        if (intervals[i][0] <= last[1]) {
            // Overlaps: extend the end of the current merged interval if needed
            last[1] = max(last[1], intervals[i][1]);
        } else {
            // No overlap: start a new interval in result
            result.push_back(intervals[i]);
        }
    }
    return result;
}

int main() {
    vector<vector<int>> iv1 = {{1,3},{2,6},{8,10},{15,18}};
    for (auto& r : merge(iv1))
        std::cout << '[' << r[0] << ',' << r[1] << "] "; // [1,6] [8,10] [15,18]
    std::cout << '\n';

    vector<vector<int>> iv2 = {{1,4},{4,5}};
    for (auto& r : merge(iv2))
        std::cout << '[' << r[0] << ',' << r[1] << "] "; // [1,5]
    std::cout << '\n';
    return 0;
}
