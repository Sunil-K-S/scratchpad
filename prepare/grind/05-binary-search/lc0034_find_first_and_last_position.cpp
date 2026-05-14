/**
 * LeetCode 34 — Find First and Last Position of Element in Sorted Array
 * Difficulty: Medium
 *
 * PROBLEM:
 *   Non-decreasing nums (duplicates allowed), target. Return {first, last}
 *   index of target, or {-1,-1} if absent.
 *
 * CONSTRAINTS:
 *   0 <= nums.length <= 10^5
 *   -10^9 <= nums[i], target <= 10^9
 *
 * LOGIC:
 *   Two binary searches:
 *   - leftMost: first i with nums[i] >= target, then verify nums[i]==target.
 *   - rightMost: first i with nums[i] > target, answer is i-1.
 *
 *   "First > target" is upper_bound; subtract 1 for last >= target.
 *
 * TIME:  O(log n)
 * SPACE: O(1)
 *
 * CORNER CASES:
 *   - empty nums -> {-1,-1}
 *   - all elements target -> [0, n-1]
 *   - single element
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * WORKED EXAMPLE  (nums = [5, 7, 7, 8, 8, 10], target = 8)
 * ─────────────────────────────────────────────────────────────────────────────
 *   lower_bound(8): first i with nums[i] >= 8 → i=3, nums[3]==8 ✓  → first = 3
 *   upper_bound(8): first i with nums[i] > 8  → i=5 (value 10)
 *   last position = upper_bound(8) - 1 = 4  (second 8)  → answer [3,4] ✓
 *
 *   target = 6 (not in array):
 *   lower_bound(6) lands on first 7 at index 1, nums[1]!=6 → return [-1,-1]

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Binary search for range boundaries is fundamental in database systems:
 *   - B-Tree range scans: finding the first and last leaf page entries for a
 *     SQL range query (WHERE date BETWEEN x AND y) uses exactly this pattern.
 *   - Log file indexing: find the start and end byte offset of all logs for
 *     a given hour, given a sorted timestamp index.
 *   - Event sourcing: locate all events for a given aggregate ID in an
 *     append-only sorted event store.
 */

#include <iostream>
#include <vector>

using namespace std;

int lowerBound(const vector<int>& nums, int x) {
    int lo = 0;
    int hi = static_cast<int>(nums.size());
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (nums[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int upperBound(const vector<int>& nums, int x) {
    int lo = 0;
    int hi = static_cast<int>(nums.size());
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (nums[mid] <= x) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

vector<int> searchRange(const vector<int>& nums, int target) {
    if (nums.empty()) {
        return {-1, -1};
    }
    const int L = lowerBound(nums, target);
    if (L == static_cast<int>(nums.size()) || nums[L] != target) {
        return {-1, -1};
    }
    const int R = upperBound(nums, target) - 1;
    return {L, R};
}

int main() {
    auto a = searchRange({5, 7, 7, 8, 8, 10}, 8);
    cout << a[0] << ' ' << a[1] << '\n'; // 3 4
    auto b = searchRange({5, 7, 7, 8, 8, 10}, 6);
    cout << b[0] << ' ' << b[1] << '\n'; // -1 -1
    return 0;
}
