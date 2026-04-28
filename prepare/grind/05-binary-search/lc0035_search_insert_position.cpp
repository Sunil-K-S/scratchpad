/**
 * LeetCode 35 — Search Insert Position
 * Difficulty: Easy
 *
 * PROBLEM:
 *   Sorted distinct nums, target. Return index if target exists; else return
 *   the index where it would be inserted to keep order.
 *
 * CONSTRAINTS:
 *   1 <= nums.length <= 10^4
 *   -10^4 < nums[i] < 10^4
 *   distinct, sorted ascending
 *
 * LOGIC:
 *   Classic lower_bound: first index i such that nums[i] >= target.
 *   When target absent, that i is exactly the insert position.
 *
 *   Template: lo = 0, hi = n (half-open [lo, hi) over indices); while lo < hi:
 *   mid = (lo+hi)/2; if nums[mid] < target -> answer in (mid, hi) so lo = mid+1;
 *   else hi = mid. End: lo == first position with nums[lo] >= target.
 *
 * TIME:  O(log n)
 * SPACE: O(1)
 *
 * CORNER CASES:
 *   - target less than nums[0] -> 0
 *   - target greater than all -> n
 *   - target equals some element -> that index

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Finding the insertion point in a sorted structure is core to many systems:
 *   - Order book management: insert a new buy/sell order at the correct price
 *     position in a sorted order book (std::lower_bound is this exact function).
 *   - Version management: find where a new version tag belongs in a sorted
 *     release history.
 *   - Leaderboards: find the rank of a new score in a sorted leaderboard,
 *     then insert it at the right position.
 */

#include <iostream>
#include <vector>

using namespace std;

int searchInsert(const vector<int>& nums, int target) {
    int lo = 0;
    int hi = static_cast<int>(nums.size());
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (nums[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int main() {
    cout << searchInsert({1, 3, 5, 6}, 5) << '\n'; // 2
    cout << searchInsert({1, 3, 5, 6}, 2) << '\n'; // 1
    cout << searchInsert({1, 3, 5, 6}, 7) << '\n'; // 4
    return 0;
}
