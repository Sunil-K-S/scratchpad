/**
 * LeetCode 78 — Subsets
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return all possible subsets (the power set) of an array of distinct integers.
 *
 *   Example: nums=[1,2,3]
 *   Output: [[],[1],[2],[3],[1,2],[1,3],[2,3],[1,2,3]]
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Backtracking — decide include/exclude for each element
 * ─────────────────────────────────────────────────────────────────────────────
 *   At each position `start`, we CHOOSE to include elements from start..n-1.
 *   For each choice of element i (i >= start), add nums[i] to current subset,
 *   recurse from i+1, then remove nums[i] (backtrack).
 *
 *   DECISION TREE for [1,2,3]:
 *   []
 *   ├── [1]
 *   │   ├── [1,2]
 *   │   │   └── [1,2,3] ✓
 *   │   └── [1,3] ✓
 *   ├── [2]
 *   │   └── [2,3] ✓
 *   └── [3] ✓
 *   (Plus [] itself)
 *
 *   Every node in this tree is a valid subset — we record ALL nodes, not just leaves.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * ALTERNATIVE: Bitmask (good to mention)
 * ─────────────────────────────────────────────────────────────────────────────
 *   For n <= 20, iterate mask from 0 to (1<<n)-1.
 *   Bit j set in mask → include nums[j].
 *   2^n total masks = 2^n subsets.
 *   Simpler for small n, but backtracking scales better conceptually.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n * 2^n) — 2^n subsets, each takes O(n) to copy
 *   SPACE: O(n) recursion depth + O(n * 2^n) for output
 *
 * CORNER CASES:
 *   Empty array → [[]] (one subset: the empty set)
 *   Single element → [[], [x]]

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Power set enumeration is used whenever you need to explore all combinations:
 *   - Feature engineering (ML): generate all subsets of features to evaluate
 *     which combination produces the best model (wrapper-based feature selection).
 *   - A/B testing configuration: enumerate all subsets of UI changes to find
 *     which combination maximizes conversion rate.
 *   - Test case generation: enumerate all subsets of input flags to achieve
 *     combinatorial test coverage.
 *   - Configuration management: find all valid subsets of optional microservice
 *     dependencies that satisfy constraints.
 */

#include <iostream>
#include <vector>

using namespace std;

void backtrack(const vector<int>& nums, int start,
               vector<int>& current, vector<vector<int>>& result) {
    result.push_back(current); // record current subset at every call (not just leaf)

    for (int i = start; i < static_cast<int>(nums.size()); ++i) {
        current.push_back(nums[i]); // choose nums[i]
        backtrack(nums, i + 1, current, result); // recurse: next element must be after i
        current.pop_back(); // unchoose (backtrack)
    }
}

vector<vector<int>> subsets(const vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> current;
    backtrack(nums, 0, current, result);
    return result;
}

int main() {
    for (auto& s : subsets({1,2,3})) {
        std::cout << '[';
        for (int i = 0; i < static_cast<int>(s.size()); ++i)
            std::cout << (i ? "," : "") << s[i];
        std::cout << "]\n";
    }
    // [], [1], [1,2], [1,2,3], [1,3], [2], [2,3], [3]
    return 0;
}
