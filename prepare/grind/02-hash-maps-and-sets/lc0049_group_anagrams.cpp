/**
 * LeetCode 49 — Group Anagrams
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given an array of strings, group strings that are anagrams together.
 *   Return groups in any order; within a group, any order is fine.
 *
 *   Example: ["eat","tea","tan","ate","nat","bat"]
 *   Output:  [["eat","tea","ate"], ["tan","nat"], ["bat"]]
 *
 * CONSTRAINTS:
 *   1 <= strs.length <= 10^4
 *   0 <= strs[i].length <= 100
 *   strs[i] contains only lowercase English letters
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Anagrams share a canonical "signature"
 * ─────────────────────────────────────────────────────────────────────────────
 *   Two strings are anagrams iff they have the same character multiset.
 *   → Compute a "signature" for each string, use it as a map key.
 *   → All strings with the same signature go into the same bucket.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * TWO SIGNATURE OPTIONS (know both for interview)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Option A — Sort the string (used here):
 *     "eat" → sort → "aet"
 *     "tea" → sort → "aet"   ← same key → same group
 *     Cost: O(k log k) per string where k = string length.
 *
 *   Option B — Count 26 characters, encode as string:
 *     "eat" → [1,0,0,0,1,0,...,1,...,0] → "1#0#0#...#1#...#0"
 *     Cost: O(k) per string — better when strings are long and alphabet is small.
 *     Trade-off: slightly more complex code; marginal gain for k<=100.
 *
 *   → In an interview, implement Option A (simpler), then mention Option B
 *     as an O(N*K) optimization if interviewer asks.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * ALGORITHM
 * ─────────────────────────────────────────────────────────────────────────────
 *   For each string s:
 *     1. key = sort(s)
 *     2. buckets[key].push_back(s)
 *   Return all bucket value-lists.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (strs = ["eat","tea","tan","ate","nat","bat"])
 * ─────────────────────────────────────────────────────────────────────────────
 *   Process "eat" → key="aet"  → buckets["aet"] = ["eat"]
 *   Process "tea" → key="aet"  → buckets["aet"] = ["eat","tea"]
 *   Process "tan" → key="ant"  → buckets["ant"] = ["tan"]
 *   Process "ate" → key="aet"  → buckets["aet"] = ["eat","tea","ate"]
 *   Process "nat" → key="ant"  → buckets["ant"] = ["tan","nat"]
 *   Process "bat" → key="abt"  → buckets["abt"] = ["bat"]
 *
 *   Result: [["eat","tea","ate"], ["tan","nat"], ["bat"]]  ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(N * K log K) — N strings, each sorted in O(K log K)
 *   SPACE: O(N * K) — storing all characters in the map (keys + values)
 *   (Option B would be O(N * K) time with O(N * K) space)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   [""]          → [[""]]: empty string sorts to "", valid group of one
 *   ["a","b","c"] → [["a"],["b"],["c"]]: no anagrams, each alone
 *   ["z","z"]     → [["z","z"]]: duplicates are valid anagrams of each other
 *
 * INTERVIEW TIP:
 *   Mention: "Anagrams have the same sorted form — that's the key.
 *   If strings are long (k >> 26), I'd use a count-array key to reduce
 *   O(k log k) per string to O(k)."

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Canonical key grouping is the backbone of many clustering problems:
 *   - Spell checkers / autocorrect: group words by sorted characters to suggest
 *     alternatives (e.g., silent -> listen, enlist).
 *   - Search deduplication: group URLs by their canonical form to avoid serving
 *     the same page under multiple paths.
 *   - Log analysis: group log lines with the same signature to find recurring
 *     error patterns without caring about variable parts.
 *   - Plagiarism detection: normalize and sort tokens to identify reordered text.
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string> strs) {
    unordered_map<string, vector<string>> buckets;
    buckets.reserve(strs.size() * 2);

    for (string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        buckets[std::move(key)].push_back(std::move(s));
    }

    vector<vector<string>> out;
    out.reserve(buckets.size());
    for (auto& [k, vec] : buckets) {
        (void)k;
        out.push_back(std::move(vec));
    }
    return out;
}

int main() {
    auto ans = groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"});
    cout << ans.size() << " groups\n"; // expect 3 groups
    return 0;
}
