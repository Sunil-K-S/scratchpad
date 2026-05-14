/**
 * LeetCode 78 — Subsets (Bitmask variant)
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return all subsets of nums (same problem as 13-backtracking/lc0078_subsets.cpp)
 *   but solved using bitmask enumeration.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Each bit in an integer represents include/exclude per element
 * ─────────────────────────────────────────────────────────────────────────────
 *   For n elements, there are 2^n subsets = masks 0 .. (1<<n)-1.
 *   For mask m: if bit j is set (m & (1<<j)) → include nums[j].
 *
 *   STEP-BY-STEP TRACE: nums=[a,b,c], mask=0b101=5 → include indices 0 and 2 → {a,c}
 *
 *   mask=0b000=0 → {} (empty set)
 *   mask=0b001=1 → {a}
 *   mask=0b010=2 → {b}
 *   mask=0b011=3 → {a,b}
 *   mask=0b100=4 → {c}
 *   mask=0b101=5 → {a,c}
 *   mask=0b110=6 → {b,c}
 *   mask=0b111=7 → {a,b,c}
 *
 *   WHY USE THIS vs backtracking:
 *   - Simpler, no recursion
 *   - Limited to n <= 30 (int) or n <= 62 (long long)
 *   - Backtracking more general (handles duplicates, early termination)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n * 2^n) — 2^n masks, each check n bits
 *   SPACE: O(1) extra (O(n * 2^n) for output)
 *
 * CORNER CASES:
 *   Empty array → 1 mask (000) → [[]]
 *   n > 30: need long long or different approach

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Bitmask enumeration of subsets is the standard technique in permission and
 *   configuration systems:
 *   - Unix file permissions: rwxrwxrwx is a 9-bit mask; enumerating subsets
 *     generates all possible permission combinations.
 *   - Feature flags (LaunchDarkly, Unleash): each user cohort has a bitmask of
 *     enabled features; iterating subsets evaluates all flag combinations.
 *   - Dynamic programming on subsets (bitmask DP): TSP, Hamiltonian path, and
 *     minimum Steiner tree algorithms use bitmask to represent visited node sets.
 *   - Hardware instruction encoding: CPU instruction decoders enumerate opcode
 *     field subsets to match instruction patterns.
 */

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> subsetsBitmask(const vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    int total = 1 << n; // 2^n
    vector<vector<int>> result;
    result.reserve(total);

    for (int mask = 0; mask < total; ++mask) {
        vector<int> subset;
        for (int j = 0; j < n; ++j) {
            if (mask & (1 << j)) { // bit j is set → include nums[j]
                subset.push_back(nums[j]);
            }
        }
        result.push_back(move(subset));
    }
    return result;
}

int main() {
    for (auto& s : subsetsBitmask({1,2,3})) {
        std::cout << '[';
        for (int i = 0; i < static_cast<int>(s.size()); ++i)
            std::cout << (i ? "," : "") << s[i];
        std::cout << "]\n";
    }
    // 8 subsets printed in mask order
    return 0;
}
