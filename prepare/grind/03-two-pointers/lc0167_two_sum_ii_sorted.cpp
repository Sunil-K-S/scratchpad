/**
 * LeetCode 167 — Two Sum II - Input Array Is Sorted
 * Difficulty: Medium
 *
 * PROBLEM:
 *   1-indexed sorted array of distinct integers. Find two distinct indices
 *   i < j with numbers[i] + numbers[j] == target. Guaranteed exactly one answer.
 *
 * CONSTRAINTS:
 *   2 <= numbers.length <= 3 * 10^4
 *   sorted ascending, distinct values
 *
 * LOGIC:
 *   Brute force pairs -> O(n^2).
 *
 *   Two pointers L=0, R=n-1:
 *   - If sum == target -> done.
 *   - If sum < target -> need larger sum -> move L right (array sorted up).
 *   - If sum > target -> need smaller sum -> move R left.
 *
 *   Invariant: if a solution (i*, j*) exists with i* < j*, our window always
 *   contains some pair that could still be the answer until we hit it — classic
 *   monotonicity from sorting.
 *
 * TIME:  O(n)
 * SPACE: O(1)
 *
 * CORNER CASES:
 *   - n == 2 -> single valid pair
 *   - sum never crosses? (guaranteed one solution)
 *   - Use 1-based indices in the return value per problem statement
 *
 * CONTRAST with LC 1 (unsorted):
 *   Sorting would be O(n log n) and destroys original indices — so hash map
 *   is better for LC 1; two pointers shine when sorted or when sorting is free.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Two-pointer on sorted data is the workhorse of database merge operations:
 *   - Database index merge join: scan two sorted B-Tree leaf pages simultaneously
 *     to find matching keys without a hash table.
 *   - Inventory matching: match buy orders and sell orders in sorted order books.
 *   - Data reconciliation: merge two sorted audit logs to find matching events.
 *   - Genomics: find pairs of DNA positions that sum to a target offset in a
 *     sorted coordinate file.
 */

#include <iostream>
#include <vector>

using namespace std;

vector<int> twoSumSorted1Indexed(const vector<int>& numbers, int target) {
    int L = 0;
    int R = static_cast<int>(numbers.size()) - 1;
    while (L < R) {
        const long long sum = static_cast<long long>(numbers[L]) + numbers[R];
        if (sum == target) {
            return {L + 1, R + 1}; // problem wants 1-based
        }
        if (sum < target) {
            ++L;
        } else {
            --R;
        }
    }
    return {}; // guaranteed not hit
}

int main() {
    vector<int> numbers = {2, 7, 11, 15};
    auto ans = twoSumSorted1Indexed(numbers, 9);
    cout << ans[0] << ' ' << ans[1] << '\n'; // 1 2
    return 0;
}
