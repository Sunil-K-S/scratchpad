/**
 * LeetCode 76 — Minimum Window Substring
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given strings s and t, return the shortest substring of s that contains
 *   every character of t (with correct counts / multiset match).
 *   If no such substring exists, return "".
 *
 *   Example: s = "ADOBECODEBANC", t = "ABC"
 *   Output: "BANC"  (positions 9-12, length 4)
 *
 * CONSTRAINTS:
 *   1 <= s.length, t.length <= 10^5
 *   s and t contain uppercase/lowercase English letters
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Sliding window with "formed" counter
 * ─────────────────────────────────────────────────────────────────────────────
 *   We want the shortest VALID window. A window is valid when it contains at
 *   least need[c] copies of every character c in t.
 *
 *   Instead of checking all character counts on every step (O(alphabet)),
 *   maintain a single integer `formed`:
 *     formed = number of DISTINCT characters in t that the current window
 *              has satisfied (i.e., window_count[c] >= need[c]).
 *   Window is valid iff formed == required_unique.
 *
 *   Pattern: expand right until valid → shrink left while still valid → repeat.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * ALGORITHM
 * ─────────────────────────────────────────────────────────────────────────────
 *   1. Build need[c] = count of c required (from t).
 *      required_unique = distinct chars in need.
 *   2. Expand R: add s[R] to window.
 *      If window[s[R]] just reached need[s[R]], increment formed.
 *   3. While formed == required_unique (window is valid):
 *      a. Update best answer (R - L + 1 if smaller than best).
 *      b. Remove s[L] from window.
 *         If window[s[L]] drops below need[s[L]], decrement formed.
 *      c. L++.
 *   4. Repeat until R reaches end of s.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (s = "ADOBECODEBANC", t = "ABC")
 * ─────────────────────────────────────────────────────────────────────────────
 *   need = {A:1, B:1, C:1}, required_unique = 3
 *   Indices:  0 1 2 3 4 5 6 7 8 9 10 11 12
 *   Chars:    A D O B E C O D E B  A  N  C
 *
 *   Expand:
 *   R=0 (A): window={A:1} → A satisfied → formed=1
 *   R=1 (D): window={A:1,D:1} → formed=1
 *   R=2 (O): window={...,O:1} → formed=1
 *   R=3 (B): window={...,B:1} → B satisfied → formed=2
 *   R=4 (E): window={...,E:1} → formed=2
 *   R=5 (C): window={...,C:1} → C satisfied → formed=3  ← VALID!
 *
 *   Shrink from L=0:
 *     Window "ADOBEC", len=6, best=(0,6).
 *     Remove A: window[A]=0 < need[A]=1 → formed=2. L=1.
 *
 *   Expand again:
 *   R=6 (O): window={...,O:2} → formed=2
 *   R=7 (D): window={...,D:2} → formed=2
 *   R=8 (E): window={...,E:2} → formed=2
 *   R=9 (B): window={...,B:2} → formed=2
 *   R=10(A): window={...,A:1} → A satisfied → formed=3  ← VALID!
 *
 *   Shrink from L=1:
 *     Window "DOBECODEBA", len=10 > 6, no update.
 *     Remove D: window[D]=1, D not in need → formed stays 3. L=2.
 *     Window "OBECODEBA", len=9 > 6, no update.
 *     Remove O: not in need → formed stays 3. L=3.
 *     Window "BECODEBA", len=8 > 6, no update.
 *     Remove B: window[B]=1 >= need[B]=1 → formed stays 3. L=4.
 *     Window "ECODEBA", len=7 > 6, no update.
 *     Remove E: not in need → formed stays 3. L=5.
 *     Window "CODEBA", len=6, tie with best — no improvement. L=6.
 *     Remove C: window[C]=0 < need[C]=1 → formed=2. L=7.
 *
 *   Expand:
 *   R=11(N): window={...,N:1} → formed=2
 *   R=12(C): window={...,C:1} → C satisfied → formed=3  ← VALID!
 *
 *   Shrink from L=7:
 *     Window "DEBANC", len=6, tie — no improvement. L=8.
 *     Remove D: not in need → formed=3. L=8.
 *     Window "EBANC", len=5 < 6 → best=(8,5). L=9.
 *     Remove E: not in need → formed=3.
 *     Window "BANC", len=4 < 5 → best=(9,4). L=10.
 *     Remove B: window[B]=0 < 1 → formed=2. L=11.
 *
 *   R=13: done.
 *   Answer: s.substr(9, 4) = "BANC"  ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(|s| + |t|) — each index of s enters and leaves window once
 *   SPACE: O(1) if alphabet is fixed (128 ASCII chars), else O(|alphabet|)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   t longer than s         → "" immediately (early return)
 *   s == t                  → s itself
 *   t has duplicates ("AAB")→ window[A] must reach 2 before formed increments
 *   answer at very end of s → algorithm handles; update best on every valid window
 *
 * INTERVIEW TIP:
 *   The `formed` counter is the key simplification. Without it, checking
 *   validity requires scanning all characters in t (O(|t|) per step).
 *   With it, we check validity in O(1) per step.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Minimum covering window finds the smallest range satisfying all requirements:
 *   - Log analysis: find the shortest time window containing all required event
 *     types (e.g., login->action->logout) to reconstruct a user session.
 *   - Search engines: find the smallest passage in a document containing all
 *     query keywords (used for snippet generation in Google/Bing results).
 *   - Monitoring systems: find the minimum alert window covering all SLA
 *     violation types, to determine root cause time range.
 *   - Code editors: find the smallest selection enclosing all references to a symbol.
 */

#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

string minWindow(const string& s, const string& t) {
    if (t.empty() || s.size() < t.size()) {
        return "";
    }

    unordered_map<char, int> need;
    for (char c : t) {
        need[c]++;
    }
    const int required_unique = static_cast<int>(need.size());

    unordered_map<char, int> window;
    int formed = 0;
    int L = 0;
    int best_L = 0;
    int best_len = INT_MAX;

    for (int R = 0; R < static_cast<int>(s.size()); ++R) {
        char c = s[R];
        window[c]++;

        if (need.count(c) && window[c] == need[c]) {
            ++formed;
        }

        while (formed == required_unique && L <= R) {
            const int cur_len = R - L + 1;
            if (cur_len < best_len) {
                best_len = cur_len;
                best_L = L;
            }
            char left = s[L];
            window[left]--;
            if (need.count(left) && window[left] < need[left]) {
                --formed;
            }
            ++L;
        }
    }

    return best_len == INT_MAX ? "" : s.substr(best_L, best_len);
}

int main() {
    cout << minWindow("ADOBECODEBANC", "ABC") << '\n'; // BANC
    cout << minWindow("a", "a") << '\n';             // a
    cout << minWindow("a", "aa") << '\n';            // ""
    return 0;
}
