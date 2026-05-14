/**
 * LeetCode 136 — Single Number
 * Difficulty: Easy
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Every element appears exactly twice except one. Find that single element.
 *   Solve in O(n) time and O(1) space.
 *
 *   Example: [4,1,2,1,2] → 4
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: XOR — duplicates cancel, single survives
 * ─────────────────────────────────────────────────────────────────────────────
 *   XOR properties:
 *   - a ^ a = 0  (same bits cancel)
 *   - a ^ 0 = a  (XOR with 0 leaves unchanged)
 *   - XOR is commutative and associative
 *
 *   XOR all elements: pairs cancel out to 0, single remains.
 *   STEP-BY-STEP TRACE on [4,1,2,1,2] (associative XOR):
 *   4^1^2^1^2 = 4 ^ (1^1) ^ (2^2) = 4 ^ 0 ^ 0 = 4 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — single pass
 *   SPACE: O(1) — just one integer
 *
 * CORNER CASES:
 *   Single element array → return that element
 *   Negative numbers → XOR works on bit representation, handles negatives correctly
 *
 * INTERVIEW TIP:
 *   This is also solvable with HashSet (O(n) space) or sorting, but XOR is the
 *   elegant O(1) space answer. The trick is recognizing the XOR cancel property.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   XOR self-canceling property is exploited in several systems:
 *   - RAID-5 parity: XOR all data drives to produce the parity drive; recover
 *     any single failed drive by XOR-ing the surviving drives with parity.
 *   - Network checksums: simple XOR checksums in Ethernet frames and some
 *     UDP protocols detect single-bit errors in O(n) time with O(1) space.
 *   - Cryptography (stream ciphers): XOR plaintext with keystream to encrypt;
 *     XOR ciphertext with keystream again to decrypt (symmetric property).
 *   - Memory fault detection: ECC RAM uses XOR parity bits to detect and
 *     correct single-bit memory errors.
 */

#include <iostream>
#include <vector>

using namespace std;

int singleNumber(const vector<int>& nums) {
    int result = 0;
    for (int x : nums) result ^= x; // duplicates cancel, single remains
    return result;
}

int main() {
    std::cout << singleNumber({4,1,2,1,2}) << '\n'; // 4
    std::cout << singleNumber({2,2,1})     << '\n'; // 1
    std::cout << singleNumber({1})         << '\n'; // 1
    return 0;
}
