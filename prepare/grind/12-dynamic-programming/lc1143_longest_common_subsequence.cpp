/**
 * LeetCode 1143 — Longest Common Subsequence
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return the length of the longest subsequence present in BOTH strings.
 *   (Subsequence: characters don't need to be contiguous, but maintain order.)
 *
 *   Example: text1="abcde", text2="ace" → 3  (LCS="ace")
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: 2D DP
 * ─────────────────────────────────────────────────────────────────────────────
 *   dp[i][j] = LCS length of text1[0..i-1] and text2[0..j-1]
 *
 *   BASE CASE: dp[i][0] = dp[0][j] = 0 (empty string has LCS 0 with anything)
 *
 *   TRANSITION:
 *   If text1[i-1] == text2[j-1]:  ← characters match!
 *     dp[i][j] = dp[i-1][j-1] + 1    (extend LCS by 1)
 *   Else:                          ← characters don't match
 *     dp[i][j] = max(dp[i-1][j],     (skip char from text1)
 *                    dp[i][j-1])      (skip char from text2)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (text1="abcde", text2="ace")
 * ─────────────────────────────────────────────────────────────────────────────
 *        ""  a   c   e
 *   ""  [ 0, 0,  0,  0]
 *   a   [ 0, 1,  1,  1]   text1[0]='a'==text2[0]='a' → dp[1][1]=dp[0][0]+1=1
 *   b   [ 0, 1,  1,  1]   'b' matches nothing
 *   c   [ 0, 1,  2,  2]   text1[2]='c'==text2[1]='c' → dp[3][2]=dp[2][1]+1=2
 *   d   [ 0, 1,  2,  2]   'd' matches nothing
 *   e   [ 0, 1,  2,  3]   text1[4]='e'==text2[2]='e' → dp[5][3]=dp[4][2]+1=3
 *   Answer: 3 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * SPACE OPTIMIZATION
 * ─────────────────────────────────────────────────────────────────────────────
 *   Notice dp[i][j] only depends on dp[i-1][j-1], dp[i-1][j], dp[i][j-1].
 *   We can use two rows (prev and curr) instead of a full 2D table.
 *   Space: O(min(m,n)) instead of O(m*n).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(m * n)
 *   SPACE: O(m * n) — or O(min(m,n)) with space optimization
 *
 * CORNER CASES:
 *   One string empty → 0
 *   Identical strings → length of string
 *   No common characters → 0

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   LCS is the core of all diff and alignment tools:
 *   - git diff / unified diff: diff computes LCS of two file versions to
 *     produce the minimal add/remove patch — this is the exact algorithm.
 *   - DNA / protein sequence alignment: bioinformatics tools (BLAST, Clustal)
 *     use LCS and dynamic programming to align genomic sequences.
 *   - Plagiarism detection: compare normalized token sequences of two documents;
 *     high LCS ratio indicates copied content.
 *   - File synchronization: rsync uses a rolling checksum + LCS-like approach
 *     to send only the changed blocks.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int longestCommonSubsequence(const string& text1, const string& text2) {
    const int m = static_cast<int>(text1.size());
    const int n = static_cast<int>(text2.size());

    // dp[i][j] = LCS of text1[0..i-1] and text2[0..j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i-1] == text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1; // characters match: extend
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]); // skip one character
            }
        }
    }
    return dp[m][n];
}

int main() {
    std::cout << longestCommonSubsequence("abcde", "ace")  << '\n'; // 3
    std::cout << longestCommonSubsequence("abc",   "abc")  << '\n'; // 3
    std::cout << longestCommonSubsequence("abc",   "def")  << '\n'; // 0
    return 0;
}
