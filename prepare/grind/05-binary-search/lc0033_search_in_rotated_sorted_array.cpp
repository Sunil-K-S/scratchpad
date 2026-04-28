/**
 * LeetCode 33 — Search in Rotated Sorted Array
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   A sorted array of distinct integers was rotated at some unknown pivot.
 *   e.g., [0,1,2,4,5,6,7] rotated at index 4 → [4,5,6,7,0,1,2]
 *   Return the index of target, or -1 if not found. Must be O(log n).
 *
 * CONSTRAINTS:
 *   1 <= nums.length <= 5000
 *   -10^4 <= nums[i], target <= 10^4
 *   All values distinct
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: One half is always normally sorted
 * ─────────────────────────────────────────────────────────────────────────────
 *   Even after rotation, when you pick mid, at least ONE of the two halves
 *   [lo..mid] or [mid..hi] must be sorted in normal ascending order.
 *   Why? The rotation creates at most one "break point." mid either falls in the
 *   left sorted chunk or the right sorted chunk.
 *
 *   Check: if nums[lo] <= nums[mid], the LEFT half is sorted.
 *          else the RIGHT half is sorted.
 *
 *   Then: does target fall inside the sorted half's range?
 *     YES → search that half (standard binary search move).
 *     NO  → target must be in the other half → search there.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * ALGORITHM
 * ─────────────────────────────────────────────────────────────────────────────
 *   lo=0, hi=n-1
 *   while lo <= hi:
 *     mid = lo + (hi-lo)/2
 *     if nums[mid] == target: return mid
 *
 *     if nums[lo] <= nums[mid]:          // LEFT half [lo..mid] is sorted
 *       if nums[lo] <= target < nums[mid]:  // target in left half
 *         hi = mid - 1
 *       else:                               // target in right half
 *         lo = mid + 1
 *     else:                              // RIGHT half [mid..hi] is sorted
 *       if nums[mid] < target <= nums[hi]:  // target in right half
 *         lo = mid + 1
 *       else:                               // target in left half
 *         hi = mid - 1
 *   return -1
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (nums = [4,5,6,7,0,1,2], target = 0)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Indices:  0  1  2  3  4  5  6
 *   Values:  [4, 5, 6, 7, 0, 1, 2]
 *
 *   lo=0, hi=6, mid=3, nums[3]=7. Not target(0).
 *   nums[lo=4] <= nums[mid=7]? YES → left [0..3] = [4,5,6,7] is sorted.
 *   Is 4 <= 0 < 7? NO → target in right half. lo = 4.
 *
 *   lo=4, hi=6, mid=5, nums[5]=1. Not target(0).
 *   nums[lo=0] <= nums[mid=1]? YES → left [4..5] = [0,1] is sorted.
 *   Is 0 <= 0 < 1? YES → target in left half. hi = 4.
 *
 *   lo=4, hi=4, mid=4, nums[4]=0. Found! Return 4. ✓
 *
 * TRACE (nums = [4,5,6,7,0,1,2], target = 3)
 *   lo=0, hi=6, mid=3 (7). Left sorted [4..7]. 4<=3<7? NO → lo=4.
 *   lo=4, hi=6, mid=5 (1). Left sorted [0..1]. 0<=3<1? NO → hi=4.
 *   lo=4, hi=4, mid=4 (0). Left sorted [0..0]. 0<=3<0? NO → lo=5.
 *   lo=5 > hi=4: stop. Return -1. ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(log n) — halve search space each iteration
 *   SPACE: O(1)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Not rotated [1,2,3,4,5]: nums[lo] <= nums[mid] always → left always sorted → degrades to standard binary search. Correct.
 *   Single element [5], target=5: mid=0, found immediately.
 *   Target at rotation boundary: handled by range checks.
 *
 * INTERVIEW TIP:
 *   The key phrase: "one half is always sorted." Once you identify which
 *   half that is, checking if target falls within its range is O(1),
 *   and you can discard the other half. That gives O(log n).

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Rotated sorted data appears whenever a circular structure is stored linearly:
 *   - Circular log buffers (ring buffers): OS kernel logs and network packet capture
 *     buffers overwrite oldest entries. Searching requires handling wrap-around.
 *   - Time-series data with daily rotation: sensor data rolled over at midnight
 *     can be modeled as a rotated sorted array.
 *   - Distributed systems clock drift: node timestamps can wrap; this pattern
 *     handles monotonic counter search across the wrap boundary.
 */

#include <iostream>
#include <vector>

using namespace std;

int searchRotated(const vector<int>& nums, int target) {
    int lo = 0;
    int hi = static_cast<int>(nums.size()) - 1;
    while (lo <= hi) {
        const int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[lo] <= nums[mid]) {
            // left segment sorted
            if (nums[lo] <= target && target < nums[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } else {
            // right segment sorted
            if (nums[mid] < target && target <= nums[hi]) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
    }
    return -1;
}

int main() {
    cout << searchRotated({4, 5, 6, 7, 0, 1, 2}, 0) << '\n'; // 4
    cout << searchRotated({4, 5, 6, 7, 0, 1, 2}, 3) << '\n'; // -1
    cout << searchRotated({1}, 0) << '\n';                   // -1
    return 0;
}
