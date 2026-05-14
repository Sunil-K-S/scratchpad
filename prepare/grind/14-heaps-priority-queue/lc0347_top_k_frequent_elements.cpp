/**
 * LeetCode 347 — Top K Frequent Elements
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return the k most frequent elements. Any order is acceptable.
 *
 *   Example: nums=[1,1,1,2,2,3], k=2 → [1,2]
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * TWO APPROACHES
 * ─────────────────────────────────────────────────────────────────────────────
 *
 * APPROACH 1: Min-heap of size k — O(n log k)
 * ─────────────────────────────────────────────────────────────────────────────
 *   1. Build frequency map: O(n)
 *   2. Use min-heap (keyed on frequency) of size k.
 *      For each (val, freq): push; if heap > k, pop min-freq item.
 *   3. Result = remaining heap elements.
 *
 * APPROACH 2: Bucket Sort — O(n)  ← optimal
 * ─────────────────────────────────────────────────────────────────────────────
 *   Frequencies range from 1 to n. Create n+1 buckets where bucket[i] holds
 *   all elements with frequency i. Scan from bucket[n] down to collect top-k.
 *
 *   WHY O(n): bucket array has size n+1; filling it and scanning is O(n).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   Frequency count:  O(n)
 *   Heap approach:    O(n log k)
 *   Bucket approach:  O(n)
 *
 * CORNER CASES:
 *   k == number of distinct elements → return all distinct elements
 *   All elements same frequency → any k of them
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (nums = [1,1,1,2,2,3], k = 2) — Approach 2: buckets
 * ─────────────────────────────────────────────────────────────────────────────
 *   Count freq: {1→3, 2→2, 3→1}. Buckets[i] = values with freq i.
 *     bucket[1]={3}, bucket[2]={2}, bucket[3]={1}
 *   Collect k items from highest freq downward: take {1}, then take {2} → [1,2] ✓
 *
 *   Same data with min-heap of size k on (freq, value): heap ends up holding
 *   the two smallest frequency counts among candidates — analogous to LC 215.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Top-K frequency queries are among the most common operations in analytics:
 *   - Trending topics (Twitter/X, Google Trends): find the k most mentioned
 *     hashtags or search terms in a stream of events.
 *   - Search autocomplete: suggest the k most frequently searched queries that
 *     match the current prefix (combined with a trie for prefix filtering).
 *   - Log analysis: find the top-k most frequent error codes in a log stream
 *     to prioritize incident response.
 *   - Ad tech: find the k most clicked ad creatives in a campaign to allocate
 *     more impressions to them (explore-exploit).
 */

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// ── Bucket sort approach (O(n)) ───────────────────────────────────────────────
vector<int> topKFrequent(const vector<int>& nums, int k) {
    // Step 1: count frequencies
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;

    // Step 2: bucket sort — bucket[i] = elements with frequency i
    int n = static_cast<int>(nums.size());
    vector<vector<int>> bucket(n + 1);
    for (auto& [val, count] : freq) {
        bucket[count].push_back(val);
    }

    // Step 3: collect top-k from highest frequency bucket down
    vector<int> result;
    for (int f = n; f >= 1 && static_cast<int>(result.size()) < k; --f) {
        for (int val : bucket[f]) {
            result.push_back(val);
            if (static_cast<int>(result.size()) == k) break;
        }
    }
    return result;
}

int main() {
    auto r1 = topKFrequent({1,1,1,2,2,3}, 2);
    for (int x : r1) std::cout << x << ' '; // 1 2
    std::cout << '\n';

    auto r2 = topKFrequent({1}, 1);
    for (int x : r2) std::cout << x << ' '; // 1
    std::cout << '\n';
    return 0;
}
