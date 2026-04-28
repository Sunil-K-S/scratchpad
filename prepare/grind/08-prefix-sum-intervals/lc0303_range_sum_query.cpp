/**
 * LeetCode 303 — Range Sum Query - Immutable
 * Difficulty: Easy
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given an integer array nums, handle multiple queries of sumRange(left, right)
 *   which returns sum of nums[left..right] inclusive.
 *   The array does not change (immutable). Optimize for repeated queries.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Prefix sum array
 * ─────────────────────────────────────────────────────────────────────────────
 *   Precompute prefix[i] = nums[0] + nums[1] + ... + nums[i-1]  (1-indexed, prefix[0]=0)
 *
 *   sumRange(l, r) = prefix[r+1] - prefix[l]
 *
 *   Build once in O(n), answer each query in O(1).
 *   Naive: O(n) per query → O(n*q) for q queries. Prefix sum: O(n + q).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (nums=[-2,0,3,-5,2,-1])
 * ─────────────────────────────────────────────────────────────────────────────
 *   prefix = [0, -2, -2, 1, -4, -2, -3]
 *              ^   0   1  2   3   4   5   (r+1 indices)
 *
 *   sumRange(0,2) = prefix[3] - prefix[0] = 1 - 0 = 1     ✓ (-2+0+3)
 *   sumRange(2,5) = prefix[6] - prefix[2] = -3 - (-2) = -1 ✓ (3-5+2-1)
 *   sumRange(0,5) = prefix[6] - prefix[0] = -3 - 0 = -3   ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   CONSTRUCTOR: O(n) time, O(n) space
 *   sumRange:    O(1) time per query
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   l == r           → single element, prefix[r+1] - prefix[l] = nums[l]. ✓
 *   l == 0           → prefix[r+1] - prefix[0] = prefix[r+1]. ✓
 *   Negative numbers → prefix sums still work, no special handling needed.
 *
 * INTERVIEW TIP:
 *   Prefix sums are the foundation for LC 560, LC 1480, LC 238 (product), and
 *   2D variants (LC 304 — Range Sum Query 2D). Always mention the 1D → 2D
 *   generalization for bonus signal.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Prefix sums enable O(1) range aggregate queries — the foundation of OLAP:
 *   - Data warehouses (BigQuery, Redshift): column-store engines precompute prefix
 *     sums for SUM/COUNT aggregates to answer range queries without full scans.
 *   - Game development: prefix-sum grids (2D variant) enable O(1) rectangle-sum
 *     queries for damage-area effects and terrain smoothing.
 *   - Image processing: summed area tables (2D prefix sums) accelerate box-filter
 *     convolutions used in blur, edge detection, and HAAR features.
 *   - Monitoring systems: Prometheus range queries use cumulative counters that
 *     are differenced — the same math as prefix sums in reverse.
 */

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class NumArray {
    vector<int> prefix; // prefix[i] = sum of nums[0..i-1]
public:
    explicit NumArray(vector<int>& nums) {
        prefix.resize(nums.size() + 1, 0);
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    // Sum of nums[left..right] inclusive
    int sumRange(int left, int right) const {
        return prefix[right + 1] - prefix[left];
    }
};

int main() {
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray obj(nums);
    std::cout << obj.sumRange(0, 2) << '\n'; // 1
    std::cout << obj.sumRange(2, 5) << '\n'; // -1
    std::cout << obj.sumRange(0, 5) << '\n'; // -3
    return 0;
}
