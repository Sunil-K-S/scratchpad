/**
 * LeetCode 15 — 3Sum
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given an integer array nums, return all unique triplets [a, b, c] such that
 *   they are different elements (by index) and a + b + c == 0.
 *   The answer must not contain duplicate triplets.
 *
 *   Example: nums = [-1, 0, 1, 2, -1, -4]
 *   Output:  [[-1, -1, 2], [-1, 0, 1]]
 *
 * CONSTRAINTS:
 *   3 <= nums.length <= 3000
 *   -10^5 <= nums[i] <= 10^5
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * BRUTE FORCE (don't code, just state it)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Three nested loops checking every triplet (i, j, k).
 *   Time: O(n^3)   Space: O(1)   → too slow for n = 3000
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Reduce 3Sum to repeated Two Sum II
 * ─────────────────────────────────────────────────────────────────────────────
 *   If we FIX the first number a = nums[i], we need b + c = -a.
 *   That is exactly Two Sum II on the remaining sorted subarray.
 *   Two Sum II runs in O(n) with two pointers on a sorted array.
 *   Do this for every i → O(n) * O(n) = O(n^2). Done.
 *
 *   WHY SORT?
 *   (a) Enables two-pointer technique (requires sorted order).
 *   (b) Groups duplicates together → easy to skip with a single comparison.
 *   Note: The problem asks for VALUES, not indices, so sorting is safe.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * ALGORITHM (step by step)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Step 1: Sort nums.
 *
 *   Step 2: For i = 0 to n-3:
 *     a) Skip if nums[i] == nums[i-1]  ← avoids duplicate first elements
 *     b) Prune 1: nums[i] + nums[i+1] + nums[i+2] > 0  → break
 *                 (even the three smallest remaining sum > 0, no solution possible)
 *     c) Prune 2: nums[i] + nums[n-2] + nums[n-1] < 0  → continue
 *                 (even the two largest can't compensate, skip this i)
 *     d) Set L = i+1, R = n-1, need = -nums[i]
 *
 *   Step 3: Two-pointer scan (L < R):
 *     sum = nums[L] + nums[R]
 *     • sum < need  → L++   (need larger value on left)
 *     • sum > need  → R--   (need smaller value on right)
 *     • sum == need → record triplet, then:
 *                     L++, R--
 *                     skip duplicate L: while nums[L] == nums[L-1] → L++
 *                     skip duplicate R: while nums[R] == nums[R+1] → R--
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (nums = [-4, -1, -1, 0, 1, 2] after sort)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Indices:          0    1    2    3    4    5
 *   Values:         [-4,  -1,  -1,   0,   1,   2]
 *
 *   i=0, a=-4, need=4:
 *     L=1(-1), R=5(2): sum=1 < 4  → L++
 *     L=2(-1), R=5(2): sum=1 < 4  → L++
 *     L=3(0),  R=5(2): sum=2 < 4  → L++
 *     L=4(1),  R=5(2): sum=3 < 4  → L++
 *     L=5 >= R=5: stop.  No triplet.
 *
 *   i=1, a=-1, need=1:
 *     L=2(-1), R=5(2): sum=1 == 1 → record [-1,-1,2] ✓
 *                       L→3, R→4
 *                       no duplicates to skip
 *     L=3(0),  R=4(1): sum=1 == 1 → record [-1,0,1] ✓
 *                       L→4, R→3
 *     L=4 >= R=3: stop.
 *
 *   i=2, a=-1: nums[2]==nums[1] → SKIP (would produce duplicates)
 *
 *   i=3, a=0, need=0:
 *     Prune 2: 0 + 1 + 2 = 3 > 0 … wait, check prune 1:
 *     nums[3]+nums[4]+nums[5] = 0+1+2 = 3 > 0 → break outer loop.
 *
 *   Result: [[-1,-1,2], [-1,0,1]]  ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * DUPLICATE SKIPPING — WHY THREE PLACES?
 * ─────────────────────────────────────────────────────────────────────────────
 *   Duplicates can enter from three positions in the triplet (a, b, c):
 *
 *   1) Outer loop (a): if nums[i] == nums[i-1], fixing the same 'a' again
 *      will generate the exact same set of (b,c) pairs → skip.
 *
 *   2) Left pointer (b): after recording a match, L moves right. If the new
 *      nums[L] equals the old nums[L-1], it would pair with the same R and
 *      give the same triplet → skip.
 *
 *   3) Right pointer (c): same reasoning, R moves left, skip if same value.
 *
 *   Miss any one of these → duplicate triplets in output (common bug).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PRUNING — WHY IT'S CORRECT
 * ─────────────────────────────────────────────────────────────────────────────
 *   Prune 1 (break): Array is sorted. nums[i] <= nums[i+1] <= nums[i+2].
 *   If the three smallest elements starting at i sum to > 0, then every
 *   triplet with nums[i] as anchor will also sum to > 0. No point continuing.
 *
 *   Prune 2 (continue): nums[n-2] and nums[n-1] are the two largest.
 *   If nums[i] + largest_two < 0, this anchor is too negative — move on.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n^2) — outer loop O(n), two-pointer inner loop O(n) per iteration
 *          (sorting is O(n log n), dominated by O(n^2))
 *   SPACE: O(1) extra (excluding output). Sort is in-place.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   [0,0,0,0]    → [[0,0,0]] (not four copies)
 *   [1,2,3]      → []  (no negative numbers, can never sum to 0)
 *   [-1,0,1]     → [[-1,0,1]]  (exactly one triplet)
 *   [-2,0,0,2,2] → [[-2,0,2]]  (duplicates in input, one unique triplet)
 *
 * INTERVIEW TIP:
 *   When asked "why sort?" say: "It lets me use two pointers (O(n) scan) and
 *   groups duplicates so I can skip them with a single comparison. The problem
 *   asks for values not indices, so sorting is safe."

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Three-variable constraint solving shows up whenever you fix one dimension and
 *   search the remaining two:
 *   - Financial portfolio rebalancing: find three assets whose combined weight = 1.0
 *     and whose correlation matrix is minimized.
 *   - Recommendation systems: find triples (user, item, context) satisfying a
 *     relevance threshold — used in context-aware collaborative filtering.
 *   - Chemistry/physics simulation: find atom triplets satisfying bond-angle constraints.
 *   - Database query optimization: three-table join where sum of foreign keys = X
 *     can be solved with this pattern on sorted indexes.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end()); // Step 1: sort so two-pointer works and duplicates are adjacent
    const int n = static_cast<int>(nums.size());
    vector<vector<int>> res;
    res.reserve(static_cast<size_t>(n) * 2);

    for (int i = 0; i < n - 2; ++i) {
        // Duplicate skip (position a): same anchor as previous iteration
        // would yield the same (b,c) pairs → skip to avoid duplicate triplets.
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        const int a = nums[i];

        // Prune 1 (break): nums[i], nums[i+1], nums[i+2] are the three
        // smallest values from here. If they already sum > 0, every triplet
        // anchored at i (or later) will also be > 0. No solution possible.
        if (a + nums[i + 1] + nums[i + 2] > 0) {
            break;
        }

        // Prune 2 (continue): nums[n-2], nums[n-1] are the two largest.
        // If a + the two largest < 0, this anchor is too small — move to next i.
        if (a + nums[n - 2] + nums[n - 1] < 0) {
            continue;
        }

        // Two-pointer scan on the subarray to the right of i.
        // We need nums[L] + nums[R] == -a  (i.e. a + L + R == 0)
        int L = i + 1;
        int R = n - 1;
        const int need = -a;

        while (L < R) {
            const int sum = nums[L] + nums[R];
            if (sum < need) {
                ++L; // sum too small → move left pointer right to increase sum
            } else if (sum > need) {
                --R; // sum too large → move right pointer left to decrease sum
            } else {
                // Found a valid triplet
                res.push_back({a, nums[L], nums[R]});

                // Advance both pointers past the matched values
                ++L;
                --R;

                // Duplicate skip (position b): if new nums[L] == old nums[L-1],
                // it would pair with the same R → same triplet → skip.
                while (L < R && nums[L] == nums[L - 1]) {
                    ++L;
                }

                // Duplicate skip (position c): same reasoning for right side.
                while (L < R && nums[R] == nums[R + 1]) {
                    --R;
                }
            }
        }
    }
    return res;
}

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto ans = threeSum(nums);
    cout << ans.size() << " triplets\n"; // 2: [-1,-1,2], [-1,0,1]
    return 0;
}
