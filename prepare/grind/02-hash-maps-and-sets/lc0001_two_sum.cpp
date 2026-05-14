/**
 * LeetCode 1 — Two Sum
 * Difficulty: Easy
 *
 * PROBLEM:
 *   Given an integer array nums and an integer target, return indices i != j
 *   such that nums[i] + nums[j] == target. Exactly one solution exists.
 *
 * CONSTRAINTS:
 *   2 <= nums.length <= 10^4
 *   -10^9 <= nums[i] <= 10^9
 *   -10^9 <= target <= 10^9
 *
 * LOGIC:
 *   Brute force: check all pairs (i,j) -> O(n^2) time, O(1) space.
 *
 *   Optimized: one pass with hash map value -> index.
 *   For each index i, we need earlier index j with nums[j] == target - nums[i].
 *   If complement exists in map, we found the pair; else store nums[i] -> i.
 *
 *   Why one pass works: when we are at i, all indices < i are already in the map,
 *   so we never use the same element twice (unless problem allowed it — then
 *   you'd need different handling).
 *
 * TIME:  O(n) — each element inserted once, O(1) average map ops
 * SPACE: O(n) — map holds up to n entries
 *
 * CORNER CASES:
 *   - Exactly two elements that sum to target (minimal input)
 *   - Negative numbers / zero (still fine; map keys are full int range)
 *   - Duplicate values: map stores latest index; earlier index may already be
 *     paired — but problem guarantees one valid pair; typical tests still pass
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * WORKED EXAMPLE  (nums = [2, 7, 11, 15], target = 9)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Map stores value → index for elements already scanned.
 *
 *   i=0, nums[0]=2: need = 9-2 = 7. Map has no 7. Insert map[2]=0.   map={2→0}
 *   i=1, nums[1]=7: need = 9-7 = 2. Map has 2 at index 0. Return [0,1].
 *   Check: nums[0]+nums[1]=2+7=9 ✓
 *
 *   Second example: nums = [3, 3], target = 6
 *   i=0: need=3, not in map. map[3]=0.
 *   i=1: need=3, found at 0. Return [0,1].
 *
 * NOTE FOR LEETCODE:
 *   Remove or rename main() before pasting; LeetCode provides its own driver.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   The complement-lookup pattern (store what you have seen, query for what you need)
 *   appears constantly in production code:
 *   - E-commerce: find two products whose prices sum to a gift card value.
 *   - Accounting/reconciliation: match debit entries against credit entries.
 *   - Networking: match TCP SYN packets to SYN-ACK responses in connection tracking.
 *   - Compilers: symbol table lookup — have I seen this variable before?
 *   Hash map as an O(1) cache is the core pattern behind Redis, Memcached,
 *   and every in-process cache you will build.
 */

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> twoSum(const vector<int>& nums, int target) {
    unordered_map<int, int> value_to_index;
    value_to_index.reserve(nums.size() * 2);

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        const int need = target - nums[i];
        auto it = value_to_index.find(need);
        if (it != value_to_index.end()) {
            return {it->second, i};
        }
        value_to_index[nums[i]] = i;
    }
    return {}; // unreachable if problem guarantees a solution
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    auto ans = twoSum(nums, target);
    // Expected: {0, 1} because nums[0]+nums[1]==9
    cout << ans[0] << ' ' << ans[1] << '\n';

    vector<int> nums2 = {3, 3};
    auto ans2 = twoSum(nums2, 6);
    cout << ans2[0] << ' ' << ans2[1] << '\n'; // {0,1}

    return 0;
}
