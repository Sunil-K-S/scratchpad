/**
 * LeetCode 179 — Largest Number
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given a list of non-negative integers, arrange them to form the largest
 *   possible number and return it as a string.
 *
 *   Example: [3, 30, 34, 5, 9]  → "9534330"
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Custom comparator — compare concatenations
 * ─────────────────────────────────────────────────────────────────────────────
 *   For two numbers a and b, which comes first?
 *   Compare the string a+b vs b+a (concatenation).
 *   If "a+b" > "b+a" lexicographically (as numbers), put a before b.
 *
 *   STEP-BY-STEP TRACE (pairwise rule):
 *   Example: a=9, b=34 → "934" vs "349" → 934 > 349 → 9 first.
 *   Example: a=3, b=30 → "330" vs "303" → 330 > 303 → 3 first.
 *
 *   WHY this works: The comparator is transitive, so sort is well-defined.
 *   Proof sketch: if ab > ba and bc > cb, then ac > ca (can be verified).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASE: All zeros
 * ─────────────────────────────────────────────────────────────────────────────
 *   Input [0, 0] → after sort → "00" → should return "0", not "00".
 *   Check: if result starts with '0', return "0".
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n log n * k) where k = average digit count (string compare O(k))
 *   SPACE: O(n * k) for string representations
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   [0, 0]       → "0"
 *   [1]          → "1"
 *   [10, 2]      → "210" ("210" > "102")

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Custom comparator-based sorting appears in many ranking and formatting problems:
 *   - Version sorting: sort semantic versions (1.10 > 1.9) requires a custom
 *     comparator, not lexicographic order.
 *   - Leaderboard construction: rank players by a composite score using a
 *     custom comparator.
 *   - File system: natural sort for filenames (file2 < file10) uses this idea.
 *   - Database ORDER BY with custom collation: DB engines plug in user-defined
 *     comparators for locale-sensitive or domain-specific ordering.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string largestNumber(vector<int>& nums) {
    vector<string> strs;
    strs.reserve(nums.size());
    for (int n : nums) strs.push_back(to_string(n));

    sort(strs.begin(), strs.end(),
         [](const string& a, const string& b) {
             return a + b > b + a; // larger concatenation goes first
         });

    // Edge case: all zeros
    if (strs[0] == "0") return "0";

    string result;
    for (const string& s : strs) result += s;
    return result;
}

int main() {
    vector<int> v1 = {3, 30, 34, 5, 9};
    std::cout << largestNumber(v1) << '\n'; // 9534330

    vector<int> v2 = {10, 2};
    std::cout << largestNumber(v2) << '\n'; // 210

    vector<int> v3 = {0, 0};
    std::cout << largestNumber(v3) << '\n'; // 0
    return 0;
}
