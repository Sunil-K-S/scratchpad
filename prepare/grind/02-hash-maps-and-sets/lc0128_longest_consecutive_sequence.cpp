/**
 * LeetCode 128 — Longest Consecutive Sequence
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given an unsorted array of integers, return the length of the longest
 *   consecutive elements sequence. Must run in O(n).
 *
 *   Example: nums=[100,4,200,1,3,2] → 4  (sequence: 1,2,3,4)
 *            nums=[0,3,7,2,5,8,4,6,0,1] → 9  (0..8)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Only count from sequence STARTS
 * ─────────────────────────────────────────────────────────────────────────────
 *   BRUTE FORCE: Sort, then scan for consecutive runs → O(n log n).
 *
 *   OPTIMAL: Put all numbers in a hash set (O(1) lookup).
 *   For each number n, only start counting if (n-1) is NOT in the set.
 *   That means n is the beginning of a sequence.
 *   From there, keep incrementing (n+1, n+2, ...) while in set.
 *
 *   WHY O(n): Each number is "touched" at most twice:
 *   once when we check if it's a start, once when we count through from the start.
 *   Total work across all start-sequences = O(n).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * ALGORITHM
 * ─────────────────────────────────────────────────────────────────────────────
 *   1. Insert all nums into unordered_set.
 *   2. For each num in set:
 *      a. Skip if (num-1) is in set (not a sequence start).
 *      b. Otherwise: count = 1; while (num+count) in set → count++.
 *      c. Update global max.
 *   3. Return max.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  ([100,4,200,1,3,2])
 * ─────────────────────────────────────────────────────────────────────────────
 *   Set: {100,4,200,1,3,2}
 *
 *   num=100: 99 not in set → START. 101 not in set → count=1. max=1
 *   num=4:   3 in set → SKIP (not a start)
 *   num=200: 199 not in set → START. 201 not in set → count=1. max=1
 *   num=1:   0 not in set → START. 2 in set → 3 in set → 4 in set → 5 not in set.
 *            count=4. max=4
 *   num=3:   2 in set → SKIP
 *   num=2:   1 in set → SKIP
 *
 *   Result: 4
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — each element processed at most twice
 *   SPACE: O(n) — hash set
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Empty array        → 0
 *   All same value     → 1 (duplicates don't extend a sequence)
 *   Single element     → 1
 *   Negative numbers   → handled correctly (e.g., -3,-2,-1,0,1 → length 5)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Finding the longest run of consecutive values appears in data quality and
 *   stream analysis:
 *   - Database integrity checks: find the longest run of consecutive IDs to
 *     detect gaps (missing records) in an auto-increment primary key sequence.
 *   - Time-series analysis: find the longest streak of consecutive days a user
 *     was active (daily login streaks, Duolingo / Wordle streak logic).
 *   - Network packet analysis: find the longest run of consecutive sequence
 *     numbers received to compute the TCP receive window without gaps.
 *   - Game development: find the longest consecutive resource chain to compute
 *     combo scores or chain bonuses.
 *
 * INTERVIEW TIP:
 *   The key is recognizing that sorting would be O(n log n). The hash set trick
 *   achieves O(n) by only doing work from sequence starts — say "I only count
 *   from a number if it has no left neighbor in the set."
 */

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int longestConsecutive(const vector<int>& nums) {
    unordered_set<int> num_set(nums.begin(), nums.end());
    int max_len = 0;

    for (int n : num_set) {
        if (num_set.count(n - 1)) continue; // not a sequence start, skip

        int cur = n;
        int len = 1;
        while (num_set.count(cur + 1)) {
            cur++;
            len++;
        }
        max_len = max(max_len, len);
    }
    return max_len;
}

int main() {
    cout << longestConsecutive({100,4,200,1,3,2})        << '\n'; // 4
    cout << longestConsecutive({0,3,7,2,5,8,4,6,0,1})   << '\n'; // 9
    cout << longestConsecutive({})                        << '\n'; // 0
    cout << longestConsecutive({1})                       << '\n'; // 1
    cout << longestConsecutive({-3,-2,-1,0,1})            << '\n'; // 5
    return 0;
}
