/**
 * LeetCode 300 — Longest Increasing Subsequence
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return the length of the longest strictly increasing subsequence.
 *   (Subsequence: elements don't need to be contiguous.)
 *
 *   Example: [10,9,2,5,3,7,101,18] → 4  ([2,3,7,101] or [2,5,7,101])
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * TWO APPROACHES
 * ─────────────────────────────────────────────────────────────────────────────
 *
 * APPROACH 1: DP — O(n^2)
 * ─────────────────────────────────────────────────────────────────────────────
 *   dp[i] = length of LIS ending at index i.
 *   dp[i] = 1 + max(dp[j]) for all j < i where nums[j] < nums[i].
 *   Answer = max(dp[i]) for all i.
 *
 *   STEP-BY-STEP TRACE — DP table ([10,9,2,5,3,7,101,18]):
 *   dp = [1, 1, 1, 2, 2, 3, 4, 4]
 *   dp[3]=2 (5 extends 2), dp[4]=2 (3 extends 2), dp[5]=3 (7 extends 2,5 or 2,3)
 *   dp[6]=4 (101 extends any), dp[7]=4 (18 extends 2,3,7 or 2,5,7)
 *   Answer: 4 ✓
 *
 * APPROACH 2: Patience Sort (Binary Search) — O(n log n)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Maintain a `tails` array where tails[i] = smallest tail element of all
 *   increasing subsequences of length i+1.
 *
 *   For each num:
 *   - Binary search for first tails[j] >= num.
 *   - If found: replace tails[j] with num (keep tail as small as possible).
 *   - If not found: append num (extend longest subsequence by 1).
 *
 *   tails is always sorted, so binary search applies.
 *   tails.size() = length of LIS.
 *
 *   STEP-BY-STEP TRACE — patience / tails ([10,9,2,5,3,7,101,18]):
 *   10 → tails=[10]
 *    9 → replace 10 with 9: tails=[9]
 *    2 → replace 9 with 2: tails=[2]
 *    5 → append: tails=[2,5]
 *    3 → replace 5 with 3: tails=[2,3]
 *    7 → append: tails=[2,3,7]
 *  101 → append: tails=[2,3,7,101]
 *   18 → replace 101 with 18: tails=[2,3,7,18]
 *   tails.size() = 4 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   DP:            O(n^2) time, O(n) space
 *   Patience Sort: O(n log n) time, O(n) space
 *
 * CORNER CASES:
 *   Single element → 1
 *   Decreasing sequence [5,4,3,2,1] → 1
 *   All equal [2,2,2] → 1 (strictly increasing)

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   LIS models the longest chain of compatible or monotonically ordered events:
 *   - Version compatibility chains: find the longest chain of library versions
 *     where each version is compatible with the next.
 *   - Stock trading: find the longest run of increasing closing prices for
 *     trend analysis.
 *   - Scheduling: find the longest chain of tasks where each task start time
 *     is after the previous task end time (weighted job scheduling variant).
 *   - Patience sorting / card games: the patience sorting algorithm is equivalent
 *     to LIS and is used in card game AI solvers.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ── O(n^2) DP ────────────────────────────────────────────────────────────────
int lisDP(const vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    vector<int> dp(n, 1);
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

// ── O(n log n) Patience Sort ──────────────────────────────────────────────────
int lengthOfLIS(const vector<int>& nums) {
    vector<int> tails;
    for (int num : nums) {
        // lower_bound: first index where tails[i] >= num
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if (it == tails.end()) {
            tails.push_back(num); // extends longest subsequence
        } else {
            *it = num; // replace to keep tails as small as possible
        }
    }
    return static_cast<int>(tails.size());
}

int main() {
    vector<int> v1 = {10,9,2,5,3,7,101,18};
    std::cout << lengthOfLIS(v1) << '\n'; // 4
    std::cout << lisDP(v1) << '\n';       // 4

    std::cout << lengthOfLIS({0,1,0,3,2,3}) << '\n'; // 4
    std::cout << lengthOfLIS({7,7,7,7}) << '\n';     // 1
    return 0;
}
