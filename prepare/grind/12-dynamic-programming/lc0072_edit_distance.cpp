/**
 * LeetCode 72 — Edit Distance
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given two strings word1 and word2, return the minimum number of operations
 *   (insert, delete, replace a single character) to convert word1 into word2.
 *
 *   Example: word1="horse", word2="ros" → 3
 *   horse → rorse (replace h→r) → rose (delete r) → ros (delete e)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: 2D DP (Levenshtein Distance)
 * ─────────────────────────────────────────────────────────────────────────────
 *   dp[i][j] = min operations to convert word1[0..i-1] to word2[0..j-1]
 *
 *   BASE CASES:
 *   dp[i][0] = i  (delete i characters from word1 to reach empty word2)
 *   dp[0][j] = j  (insert j characters to reach word2 from empty word1)
 *
 *   TRANSITION:
 *   If word1[i-1] == word2[j-1]: characters match, no operation needed.
 *     dp[i][j] = dp[i-1][j-1]
 *   Else: take the minimum of three operations:
 *     dp[i][j] = 1 + min(
 *       dp[i-1][j],    // DELETE word1[i-1]: now convert word1[0..i-2] to word2[0..j-1]
 *       dp[i][j-1],    // INSERT word2[j-1]: now convert word1[0..i-1] to word2[0..j-2]
 *       dp[i-1][j-1]   // REPLACE word1[i-1] with word2[j-1]
 *     )
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (word1="horse", word2="ros")
 * ─────────────────────────────────────────────────────────────────────────────
 *        ""  r   o   s
 *   ""  [ 0, 1,  2,  3]
 *   h   [ 1, 1,  2,  3]   h≠r: min(del=1,ins=2,rep=1)+1=2? Wait: dp[0][0]+1=1 (replace h→r)
 *   o   [ 2, 2,  1,  2]   o==o: dp[1][1]=1
 *   r   [ 3, 2,  2,  2]   r==r: dp[2][0]+? No — r==r at position [3][1]: dp[2][0]=2? Hmm.
 *
 *   Full table:
 *        ""  r   o   s
 *   ""  [ 0, 1,  2,  3]
 *   h   [ 1, 1,  2,  3]
 *   o   [ 2, 2,  1,  2]
 *   r   [ 3, 2,  2,  2]
 *   s   [ 4, 3,  3,  2]
 *   e   [ 5, 4,  4,  3]
 *   Answer: dp[5][3] = 3 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(m * n)
 *   SPACE: O(m * n) — or O(min(m,n)) with space optimization (two rows)
 *
 * CORNER CASES:
 *   One string empty → length of the other (all insertions/deletions)
 *   Identical strings → 0

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Levenshtein edit distance is used wherever fuzzy matching is needed:
 *   - Spell checkers (Hunspell, aspell): find the dictionary word with minimum
 *     edit distance to the misspelled word and suggest it.
 *   - Search autocorrect (Google Did you mean?): rank query corrections
 *     by edit distance to the original query.
 *   - DNA sequence alignment: edit distance between DNA sequences identifies
 *     mutations (insertions, deletions, substitutions).
 *   - Record linkage / fuzzy join: match John Smith to Jon Smyth in a
 *     database merge by edit distance threshold.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int minDistance(const string& word1, const string& word2) {
    const int m = static_cast<int>(word1.size());
    const int n = static_cast<int>(word2.size());

    // dp[i][j] = edit distance between word1[0..i-1] and word2[0..j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Base cases
    for (int i = 0; i <= m; ++i) dp[i][0] = i; // delete all of word1
    for (int j = 0; j <= n; ++j) dp[0][j] = j; // insert all of word2

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (word1[i-1] == word2[j-1]) {
                dp[i][j] = dp[i-1][j-1]; // characters match: free
            } else {
                dp[i][j] = 1 + min({dp[i-1][j],    // delete
                                    dp[i][j-1],    // insert
                                    dp[i-1][j-1]}); // replace
            }
        }
    }
    return dp[m][n];
}

int main() {
    std::cout << minDistance("horse", "ros")    << '\n'; // 3
    std::cout << minDistance("intention", "execution") << '\n'; // 5
    std::cout << minDistance("", "abc")         << '\n'; // 3
    std::cout << minDistance("abc", "abc")      << '\n'; // 0
    return 0;
}
