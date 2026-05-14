/**
 * LeetCode 46 — Permutations
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return all possible permutations of a list of distinct integers.
 *
 *   Example: [1,2,3] → [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Backtracking — swap to mark "used"
 * ─────────────────────────────────────────────────────────────────────────────
 *   At each position `pos`, choose which remaining element goes there.
 *   Swap nums[pos] with nums[i] (i >= pos), recurse for pos+1, then swap back.
 *
 *   This avoids needing a separate `used` array — the "unused" elements are
 *   always in positions [pos..n-1] of the current array.
 *
 *   STEP-BY-STEP TRACE — decision tree for [1,2,3] (position 0 choices):
 *   pos=0: choose 1 → [1, 2,3]: recurse pos=1
 *          choose 2 → [2, 1,3]: recurse pos=1
 *          choose 3 → [3, 2,1]: recurse pos=1
 *   Each branch then picks from remaining elements for pos=1, etc.
 *   Base case: pos == n → record permutation.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n! * n) — n! permutations, each O(n) to copy
 *   SPACE: O(n) recursion depth (in-place swap avoids extra space)
 *
 * CORNER CASES:
 *   Single element → [[x]]
 *   Two elements   → [[a,b],[b,a]]

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Permutation generation is useful when order matters and all orderings must be explored:
 *   - Job shop scheduling: enumerate all orderings of tasks on a machine to
 *     find the optimal schedule (for small n; branch-and-bound uses this).
 *   - Test data generation: generate all orderings of API calls to find
 *     race conditions or state-dependent bugs.
 *   - Cryptanalysis: brute-force key permutations in small cipher keyspaces.
 *   - Route optimization (TSP for small n): enumerate all city visit orders
 *     to find the shortest tour when n <= 10.
 */

#include <iostream>
#include <vector>

using namespace std;

void backtrack(vector<int>& nums, int pos, vector<vector<int>>& result) {
    if (pos == static_cast<int>(nums.size())) {
        result.push_back(nums); // complete permutation
        return;
    }
    for (int i = pos; i < static_cast<int>(nums.size()); ++i) {
        swap(nums[pos], nums[i]);           // place nums[i] at position pos
        backtrack(nums, pos + 1, result);  // fill remaining positions
        swap(nums[pos], nums[i]);           // restore (backtrack)
    }
}

vector<vector<int>> permute(vector<int> nums) {
    vector<vector<int>> result;
    backtrack(nums, 0, result);
    return result;
}

int main() {
    for (auto& p : permute({1,2,3})) {
        for (int i = 0; i < static_cast<int>(p.size()); ++i)
            std::cout << (i ? "," : "") << p[i];
        std::cout << '\n';
    }
    // 1,2,3 / 1,3,2 / 2,1,3 / 2,3,1 / 3,2,1 / 3,1,2
    return 0;
}
