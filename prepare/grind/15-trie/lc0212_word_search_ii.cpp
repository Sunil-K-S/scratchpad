/**
 * LeetCode 212 — Word Search II
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given an m×n board and a list of words, find ALL words in board.
 *   Words must be formed by adjacent (horiz/vert) cells, no reuse per word path.
 *
 *   Example: board=[["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]]
 *   words=["oath","pea","eat","rain"] → ["eat","oath"]
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Trie + DFS — one pass of DFS finds ALL words
 * ─────────────────────────────────────────────────────────────────────────────
 *   BRUTE FORCE: Run LC79 Word Search for each word → O(W * M*N * 4^L). Too slow.
 *
 *   OPTIMAL: Build a trie from all words. Do ONE DFS traversal of the grid,
 *   following trie transitions. When a trie node has is_end=true → found a word.
 *
 *   WHY TRIE: Multiple words share prefixes. DFS terminates as soon as
 *   current path prefix isn't in trie (no need to try all W words).
 *
 *   OPTIMIZATION: After finding a word, clear its `word` field in the trie
 *   (prevents duplicates) and prune dead trie branches (no children, not end).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   Build trie: O(sum of word lengths)
 *   DFS:        O(m * n * 4^(max word length)) — shared work across words
 *   SPACE:      O(sum of word lengths) for trie
 *
 * CORNER CASES:
 *   Duplicate words in input → deduplicate in trie (only report once)
 *   Word that is prefix of another → both can be found independently
 *   Board with no words matching → empty result
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE (one word: "oath" on the LC example board)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Trie paths follow o→a→t→h. One valid DFS (down then right path):
 *     (0,0)'o' → (0,1)'a' → (1,1)'t' → (2,1)'h' → word complete, record "oath".
 *   Another DFS from other cells explores "eat" similarly. Trie pruning skips
 *   paths whose next letter is absent (e.g. no edge from trie node).

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Trie-guided multi-pattern search in a spatial structure is used in:
 *   - Aho-Corasick pattern matching: search for multiple keywords simultaneously
 *     in a text stream (used in antivirus scanners, intrusion detection systems).
 *   - Spam / content moderation filters: search for a dictionary of banned phrases
 *     in a document in one pass using a trie.
 *   - Boggle / word game solvers: find all valid words on a board given a
 *     dictionary — the classic competitive programming use case.
 *   - Genomic motif search: search for multiple gene motifs in a DNA sequence
 *     using a trie built from the motif library.
 */

#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
    array<TrieNode*, 26> children{};
    string word; // non-empty = end of word (stores the word itself)
};

void buildTrie(TrieNode* root, const vector<string>& words) {
    for (const string& w : words) {
        TrieNode* node = root;
        for (char c : w) {
            int i = c - 'a';
            if (!node->children[i]) node->children[i] = new TrieNode();
            node = node->children[i];
        }
        node->word = w;
    }
}

void dfs(vector<vector<char>>& board, int r, int c,
         TrieNode* node, vector<string>& result) {
    if (r < 0 || r >= static_cast<int>(board.size()) ||
        c < 0 || c >= static_cast<int>(board[0].size())) return;
    char ch = board[r][c];
    if (ch == '#' || !node->children[ch - 'a']) return; // visited or no trie path

    node = node->children[ch - 'a'];

    if (!node->word.empty()) {
        result.push_back(node->word);
        node->word.clear(); // deduplicate: don't report same word twice
    }

    board[r][c] = '#'; // mark visited
    dfs(board, r+1, c, node, result);
    dfs(board, r-1, c, node, result);
    dfs(board, r, c+1, node, result);
    dfs(board, r, c-1, node, result);
    board[r][c] = ch;  // restore
}

vector<string> findWords(vector<vector<char>>& board, const vector<string>& words) {
    TrieNode* root = new TrieNode();
    buildTrie(root, words);

    vector<string> result;
    for (int r = 0; r < static_cast<int>(board.size()); ++r)
        for (int c = 0; c < static_cast<int>(board[0].size()); ++c)
            dfs(board, r, c, root, result);
    return result;
}

int main() {
    vector<vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    auto res = findWords(board, {"oath","pea","eat","rain"});
    for (const string& w : res) std::cout << w << '\n';
    // eat, oath
    return 0;
}
