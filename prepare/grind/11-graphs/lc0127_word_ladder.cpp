/**
 * LeetCode 127 — Word Ladder
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given beginWord, endWord, and a wordList, return the length of the shortest
 *   transformation sequence from beginWord to endWord where:
 *   - Each step changes exactly ONE letter.
 *   - Each intermediate word must be in wordList.
 *   Return 0 if no such sequence exists.
 *
 *   Example: beginWord="hit", endWord="cog",
 *   wordList=["hot","dot","dog","lot","log","cog"]
 *   Output: 5  (hit→hot→dot→dog→cog)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: BFS on an implicit graph
 * ─────────────────────────────────────────────────────────────────────────────
 *   Each word is a node. Two words are connected if they differ by one letter.
 *   We want the SHORTEST path → BFS (not DFS).
 *
 *   We never explicitly build the graph. Instead, for each word in the queue,
 *   we generate all possible one-letter mutations (26 * len possibilities)
 *   and check if the mutation is in the word set.
 *
 *   This is O(26 * L * N) vs O(N^2 * L) for explicit graph construction.
 *   Where L = word length, N = wordList size.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (hit → cog)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Queue: [hit], level=1, wordSet={hot,dot,dog,lot,log,cog}
 *
 *   Process "hit": try h_t: aat,abt,...,hot(in set!)→ add "hot". Remove hot.
 *                  try hi_: hia,hib,...hiz. None in set.
 *                  try _it: ait,...zit. None.
 *   Queue: [hot], level=2
 *
 *   Process "hot": try _ot: dot,lot → both in set. Queue: [dot,lot], level=3
 *   Process "dot": try _ot: lot(visited). try d_t: none. try do_: dog in set.
 *   Queue: [lot,dog], level=4
 *   ...eventually reach "cog" at level=5.
 *   Answer: 5 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(N * L * 26) = O(N * L) where N=wordList size, L=word length
 *   SPACE: O(N * L) — word set + queue
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   endWord not in wordList → 0
 *   beginWord == endWord    → edge case; problem states they differ
 *   No path exists          → BFS exhausts without finding endWord → 0

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   BFS for minimum-transformation-steps models many real edit-distance problems:
 *   - NLP / word embeddings: measure semantic proximity in a word graph where
 *     edges connect words differing by one edit operation.
 *   - Genomics: find minimum point mutations to transform one DNA/protein
 *     sequence into another (minimum edit path in a mutation graph).
 *   - Compiler optimization: find minimum instruction substitutions to transform
 *     one code pattern to an equivalent optimized form.
 *   - Configuration drift recovery: find the minimum number of config changes
 *     to bring a misconfigured system back to its desired state.
 */

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int ladderLength(string beginWord, const string& endWord, vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (wordSet.find(endWord) == wordSet.end()) return 0; // endWord must be reachable

    queue<string> q;
    q.push(beginWord);
    wordSet.erase(beginWord); // mark start as visited
    int level = 1;

    while (!q.empty()) {
        int sz = static_cast<int>(q.size());
        for (int i = 0; i < sz; ++i) {
            string word = q.front(); q.pop();
            // Try changing each character to a-z
            for (int j = 0; j < static_cast<int>(word.size()); ++j) {
                char original = word[j];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == original) continue;
                    word[j] = c;
                    if (word == endWord) return level + 1;
                    if (wordSet.count(word)) {
                        q.push(word);
                        wordSet.erase(word); // remove to prevent revisiting
                    }
                    word[j] = original; // restore
                }
            }
        }
        ++level;
    }
    return 0; // no path found
}

int main() {
    vector<string> wl1 = {"hot","dot","dog","lot","log","cog"};
    std::cout << ladderLength("hit", "cog", wl1) << '\n'; // 5

    vector<string> wl2 = {"hot","dot","dog","lot","log"};
    std::cout << ladderLength("hit", "cog", wl2) << '\n'; // 0
    return 0;
}
