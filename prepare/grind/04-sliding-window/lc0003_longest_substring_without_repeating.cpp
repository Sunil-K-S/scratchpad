/**
 * LeetCode 3 — Longest Substring Without Repeating Characters
 * Difficulty: Medium
 *
 * PROBLEM:
 *   Given string s, find length of longest substring with all distinct characters.
 *
 * CONSTRAINTS:
 *   0 <= s.length <= 5 * 10^4
 *   s is English letters, digits, symbols and spaces
 *
 * LOGIC:
 *   Brute force: every substring O(n^2) substrings, each check O(n) -> O(n^3).
 *
 *   Sliding window [L, R]:
 *   Expand R to include s[R]. If s[R] already in window, shrink L until duplicate gone.
 *   Track window with a frequency map or last-seen index (last-seen is simpler here).
 *
 *   Invariant: window always has unique characters.
 *   When R advances, if char seen and its last index >= L, set L = lastIndex + 1.
 *   Then update lastIndex for s[R] and answer = max(answer, R - L + 1).
 *
 * TIME:  O(n) — L and R each move at most n steps
 * SPACE: O(min(n, alphabet)) — map of chars in window; bounded by charset size
 *
 * CORNER CASES:
 *   - Empty string -> 0
 *   - All distinct -> entire string
 *   - All same char -> 1
 *   - Answer at end of string (update max after each step)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (s = "abcabcbb")
 * ─────────────────────────────────────────────────────────────────────────────
 *   last[] stores last index of each char; L = window start; best = max length.
 *
 *   R=0 'a': last['a']=-1 < L → no jump. last['a']=0. window [0,0] len=1, best=1
 *   R=1 'b': last['b']=-1 < L. last['b']=1. [0,1] len=2, best=2
 *   R=2 'c': last['c']=-1 < L. last['c']=2. [0,2] len=3, best=3  → substring "abc"
 *   R=3 'a': last['a']=0 >= L → duplicate! L = 0+1 = 1. last['a']=3. [1,3] len=3, best=3
 *   R=4 'b': last['b']=1 >= L → L = 2. last['b']=4. [2,4] len=3, best=3
 *   R=5 'c': last['c']=2 >= L → L = 3. last['c']=5. [3,5] len=3, best=3
 *   R=6 'b': last['b']=4 >= L → L = 5. last['b']=6. [5,6] len=2, best=3
 *   R=7 'b': last['b']=6 >= L → L = 7. last['b']=7. [7,7] len=1, best=3
 *   Answer: 3  (longest without repeat is "abc")
 *
 * ALTERNATIVE:
 *   Use unordered_set + while loop to shrink from L (same complexity, more moving parts).

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   The sliding window for longest-valid-window pattern is used in:
 *   - Session token generation: ensure generated tokens have no repeating character
 *     groups (entropy validation).
 *   - Streaming deduplication: track the longest run of unique events in a stream
 *     (useful for anomaly detection: repeated identical events = incident).
 *   - Networking: TCP receive window management — track unique sequence numbers
 *     in the current window to detect retransmission.
 *   - UX: username / password validation rules (no character appears twice in a row).
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

using namespace std;

int lengthOfLongestSubstring(const string& s) {
    // Last index of each char; -1 means not in current window context
    array<int, 256> last{};
    last.fill(-1);

    int L = 0;
    int best = 0;
    for (int R = 0; R < static_cast<int>(s.size()); ++R) {
        const unsigned char c = static_cast<unsigned char>(s[R]);
        if (last[c] >= L) {
            L = last[c] + 1;
        }
        last[c] = R;
        best = max(best, R - L + 1);
    }
    return best;
}

int main() {
    cout << lengthOfLongestSubstring("abcabcbb") << '\n'; // 3 "abc"
    cout << lengthOfLongestSubstring("bbbbb") << '\n';  // 1
    cout << lengthOfLongestSubstring("") << '\n';       // 0
    return 0;
}
