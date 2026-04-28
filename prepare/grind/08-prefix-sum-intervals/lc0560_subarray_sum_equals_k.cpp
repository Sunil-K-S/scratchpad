/**
 * LeetCode 560 — Subarray Sum Equals K
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given an integer array (may have negatives!) and integer k,
 *   return the total number of subarrays that sum to k.
 *
 *   Example: nums=[1,1,1], k=2 → 2  ([1,1] starting at 0 and at 1)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Prefix sums + hash map
 * ─────────────────────────────────────────────────────────────────────────────
 *   Define prefix[i] = nums[0] + nums[1] + ... + nums[i-1]  (prefix[0]=0)
 *   Sum of subarray [j+1 .. i] = prefix[i] - prefix[j]
 *
 *   We want prefix[i] - prefix[j] == k  →  prefix[j] == prefix[i] - k
 *
 *   So for each i, count how many EARLIER prefix sums equal prefix[i] - k.
 *   Store prefix sums in a hash map (sum → frequency) as we go.
 *
 *   NOTE: This problem CANNOT use sliding window because nums may be negative
 *   (adding an element doesn't monotonically increase the sum → no invariant).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (nums=[1,1,1], k=2)
 * ─────────────────────────────────────────────────────────────────────────────
 *   prefix_count = {0:1}, running_sum = 0, count = 0
 *
 *   i=0 (val=1): sum=1. Need 1-2=-1. freq[-1]=0. count=0. Store {0:1, 1:1}.
 *   i=1 (val=1): sum=2. Need 2-2=0.  freq[0]=1.  count=1. Store {0:1, 1:1, 2:1}.
 *   i=2 (val=1): sum=3. Need 3-2=1.  freq[1]=1.  count=2. Store {0:1,1:1,2:1,3:1}.
 *   Answer: 2 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) expected (hash map ops are O(1) average)
 *   SPACE: O(n) — at most n+1 distinct prefix sums
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Negative numbers: prefix sums can decrease → sliding window wrong, this OK.
 *   k=0: subarrays that sum to 0 (possible with negatives).
 *   Single element == k: should count 1.
 *   Initialize map with {0:1} to handle subarrays starting from index 0.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Prefix sum + hash map for subarray sum queries appears in analytics:
 *   - Business analytics dashboards: count time windows (days, hours) where
 *     cumulative sales exactly reached a target revenue.
 *   - A/B testing: find all contiguous user segments where total conversions
 *     equal a target sample size.
 *   - Network traffic analysis: find all contiguous time intervals where
 *     cumulative bytes transferred equals a billing bucket boundary.
 *   - Financial auditing: find all transaction sub-sequences summing to a
 *     suspicious round amount (fraud detection).
 */

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int subarraySum(const vector<int>& nums, int k) {
    unordered_map<int, int> prefix_count;
    prefix_count[0] = 1; // empty prefix has sum 0
    int running_sum = 0;
    int count = 0;

    for (int x : nums) {
        running_sum += x;
        // How many earlier prefixes satisfy: running_sum - prefix[j] == k
        // i.e. prefix[j] == running_sum - k
        count += prefix_count[running_sum - k];
        prefix_count[running_sum]++;
    }
    return count;
}

int main() {
    std::cout << subarraySum({1,1,1}, 2) << '\n'; // 2
    std::cout << subarraySum({1,2,3}, 3) << '\n'; // 2  ([1,2] and [3])
    std::cout << subarraySum({-1,-1,1}, 0) << '\n'; // 1
    return 0;
}
