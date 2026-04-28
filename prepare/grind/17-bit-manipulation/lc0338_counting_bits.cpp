/**
 * LeetCode 338 — Counting Bits
 * Difficulty: Easy
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return an array of length n+1 where ans[i] = number of 1-bits in binary of i.
 *
 *   Example: n=5 → [0,1,1,2,1,2]
 *   (0=0b0, 1=0b1, 2=0b10, 3=0b11, 4=0b100, 5=0b101)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: DP with bit shift — every number is a right-shift plus its LSB
 * ─────────────────────────────────────────────────────────────────────────────
 *   dp[i] = dp[i >> 1] + (i & 1)
 *
 *   WHY: i >> 1 shifts right by 1 (drops LSB), which is i/2.
 *   The bit count of i = bit count of i/2 + the dropped LSB (0 or 1).
 *
 *   TRACE:
 *   dp[0] = 0
 *   dp[1] = dp[0] + (1&1) = 0 + 1 = 1
 *   dp[2] = dp[1] + (2&1) = 1 + 0 = 1  (0b10 → shift → 0b1=1 bit, +0=1)
 *   dp[3] = dp[1] + (3&1) = 1 + 1 = 2  (0b11 → shift → 0b1=1 bit, +1=2)
 *   dp[4] = dp[2] + (4&1) = 1 + 0 = 1  (0b100 → shift → 0b10=1 bit, +0=1)
 *   dp[5] = dp[2] + (5&1) = 1 + 1 = 2  (0b101 → shift → 0b10=1 bit, +1=2)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — fill array once, no __builtin_popcount needed
 *   SPACE: O(n) — output array (dp itself is the answer)
 *
 * CORNER CASES:
 *   n=0 → [0]
 *   n=1 → [0,1]

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Popcount (number of set bits) is a primitive operation in many fields:
 *   - Bloom filters: popcount the filter bit array to estimate the number of
 *     inserted elements and the false-positive rate.
 *   - Hamming distance (ML, error correction): distance between two binary
 *     vectors = popcount(a XOR b), used in near-duplicate detection and LSH.
 *   - Permission bitmasks: count how many permissions a role has by counting
 *     set bits in the permissions integer.
 *   - Compression: measure entropy of a bit stream; popcount over windows
 *     estimates local density for adaptive encoding decisions.
 */

#include <iostream>
#include <vector>

using namespace std;

vector<int> countBits(int n) {
    vector<int> dp(n + 1);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i >> 1] + (i & 1); // bit count = bit count of floor(i/2) + LSB
    }
    return dp;
}

int main() {
    for (int x : countBits(5)) std::cout << x << ' '; // 0 1 1 2 1 2
    std::cout << '\n';
    for (int x : countBits(2)) std::cout << x << ' '; // 0 1 1
    std::cout << '\n';
    return 0;
}
