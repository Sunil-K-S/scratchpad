/**
 * LeetCode 704 — Binary Search
 * Difficulty: Easy
 *
 * PROBLEM:
 *   Sorted distinct integers nums, target. Return index with nums[i] == target,
 *   or -1 if absent. O(log n) time expected.
 *
 * CONSTRAINTS:
 *   1 <= nums.length <= 10^4
 *   -10^4 < nums[i], target < 10^4
 *   nums sorted ascending, all distinct
 *
 * LOGIC:
 *   Maintain search space [lo, hi] inclusive (or half-open variant). Repeatedly
 *   compare mid to target and discard half.
 *
 *   Invariant (inclusive version): if target exists at index p, then
 *   lo <= p <= hi until found or hi < lo.
 *
 * TIME:  O(log n)
 * SPACE: O(1)
 *
 * CORNER CASES:
 *   - Single element: match / no match
 *   - target smaller than all / larger than all
 *
 * VARIANTS TO MENTION IN INTERVIEW:
 *   - First/last occurrence with duplicates -> move lo/hi asymmetrically
 *   - lower_bound / upper_bound style (see LC 35)

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Binary search is one of the most-used algorithms in computing infrastructure:
 *   - git bisect: finds the first bad commit in O(log n) steps by binary searching
 *     through commit history.
 *   - Database index lookup: B-Tree nodes use binary search within each sorted page.
 *   - Package managers: find the highest compatible version satisfying a semver
 *     constraint in a sorted release list.
 *   - Library catalog: O(log n) ISBN/title lookup vs O(n) linear scan.
 */

#include <iostream>
#include <vector>

using namespace std;

int search(const vector<int>& nums, int target) {
    int lo = 0;
    int hi = static_cast<int>(nums.size()) - 1;
    while (lo <= hi) {
        const int mid = lo + (hi - lo) / 2; // avoid (lo+hi) overflow
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}

int main() {
    cout << search({-1, 0, 3, 5, 9, 12}, 9) << '\n';  // 4
    cout << search({-1, 0, 3, 5, 9, 12}, 2) << '\n';  // -1
    return 0;
}
