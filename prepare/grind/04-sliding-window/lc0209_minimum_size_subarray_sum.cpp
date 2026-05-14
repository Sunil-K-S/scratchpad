/**
 * LeetCode 209 — Minimum Size Subarray Sum
 * Difficulty: Medium
 *
 * PROBLEM:
 *   Positive integer array nums and target sum. Find minimal length of a
 *   contiguous subarray whose sum >= target. If none, return 0.
 *
 * CONSTRAINTS:
 *   1 <= nums.length <= 10^5
 *   1 <= nums[i] <= 10^4
 *   1 <= target <= 10^9
 *   **nums[i] are positive** — critical for sliding window correctness.
 *
 * LOGIC:
 *   Because all nums[i] > 0, expanding right increases sum; shrinking left
 *   decreases sum. Maintain window [L,R] with sum >= target, minimize R-L+1.
 *
 *   Algorithm:
 *   - Expand R, add nums[R] to running sum.
 *   - While sum >= target, update answer, subtract nums[L], L++.
 *
 *   If negatives were allowed, prefix sum + deque or binary search would apply;
 *   positivity is what makes two-pointer O(n) correct.
 *
 * TIME:  O(n) — each index enters and leaves window at most once
 * SPACE: O(1)
 *
 * CORNER CASES:
 *   - Entire array needed
 *   - Single element equals target
 *   - No subarray works -> 0
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (target = 7, nums = [2, 3, 1, 2, 4, 3])
 * ─────────────────────────────────────────────────────────────────────────────
 *   After each R, extend sum; while sum >= 7, update best length = R-L+1, then
 *   sum -= nums[L], L++.
 *
 *   R=0 sum=2        (<7)
 *   R=1 sum=5        (<7)
 *   R=2 sum=6        (<7)
 *   R=3 sum=8        → win [0..3] len 4, best=4 → shrink: sum=6, L=1
 *   R=4 sum=10       → win [1..4] len 4 → shrink: sum=7, L=2 → still >=7
 *                    → win [2..4] len 3, best=3 → shrink: sum=6, L=3
 *   R=5 sum=6+3=9    → win [3..5] len 3 → shrink: sum=7, L=4 → win [4..5] len 2, best=2
 *                    → shrink: sum=3, L=5 → sum < 7, stop inner loop
 *   Answer: 2  (subarray [4, 3])
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Minimum window with a sum constraint maps to rate limiting and capacity planning:
 *   - API rate limiting: find the shortest burst window in which a client exceeded
 *     a request quota — triggers the throttle and determines reset duration.
 *   - Cloud billing: find the minimum time window where costs exceeded budget,
 *     to identify the smallest cost spike for alerting.
 *   - Network QoS: find the shortest interval over which cumulative traffic
 *     exceeded a bandwidth cap.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int minSubArrayLen(int target, const vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    long long sum = 0;
    int L = 0;
    int best = n + 1;

    for (int R = 0; R < n; ++R) {
        sum += nums[R];
        while (sum >= target) {
            best = min(best, R - L + 1);
            sum -= nums[L];
            ++L;
        }
    }
    return best == n + 1 ? 0 : best;
}

int main() {
    cout << minSubArrayLen(7, {2, 3, 1, 2, 4, 3}) << '\n'; // 2 ([4,3])
    cout << minSubArrayLen(4, {1, 4, 4}) << '\n';         // 1
    cout << minSubArrayLen(11, {1, 1, 1, 1, 1, 1, 1, 1}) << '\n'; // 0
    return 0;
}
