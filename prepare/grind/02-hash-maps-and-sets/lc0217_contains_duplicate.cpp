/**
 * LeetCode 217 — Contains Duplicate
 * Difficulty: Easy
 *
 * PROBLEM:
 *   Return true if any value appears at least twice in nums; else false.
 *
 * CONSTRAINTS:
 *   1 <= nums.length <= 10^5
 *   -10^9 <= nums[i] <= 10^9
 *
 * LOGIC:
 *   Brute force: compare all pairs -> O(n^2) time, O(1) space.
 *
 *   Optimized: hash set of seen values. For each x, if x already in set,
 *   duplicate found; else insert x. Single pass.
 *
 *   Alternative: sort and scan adjacent -> O(n log n), O(1) extra if in-place
 *   (but mutates input; often not allowed without a copy).
 *
 * TIME:  O(n) expected — O(1) expected insert and lookup per element.
 *        Worst case O(n^2) if hashing degrades (theoretical; rarely discussed for LC 217).
 * SPACE: O(n) worst case (all distinct -> full set)
 *
 * CORNER CASES:
 *   - nums.size() == 1 -> false (no pair)
 *   - Two elements equal -> true
 *   - Large positives/negatives -> fine as set keys

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Duplicate detection underpins data quality across the entire stack:
 *   - Fraud detection: flag duplicate transaction IDs submitted in a short window.
 *   - ETL pipelines: idempotency checks — have I already processed this record?
 *   - Message brokers (Kafka, SQS): exactly-once delivery uses a seen-message set.
 *   - DNS / CDN: detect duplicate resource records that would cause routing conflicts.
 *   The hash set is the go-to structure whenever you need O(1) membership testing.
 */

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

bool containsDuplicate(const vector<int>& nums) {
    unordered_set<int> seen;
    seen.reserve(nums.size() * 2);
    for (int x : nums) {
        if (seen.count(x)) {
            return true;
        }
        seen.insert(x);
    }
    return false;
}

int main() {
    cout << boolalpha;
    cout << containsDuplicate({1, 2, 3, 1}) << '\n'; // true
    cout << containsDuplicate({1, 2, 3, 4}) << '\n'; // false
    cout << containsDuplicate({1}) << '\n';           // false
    return 0;
}
