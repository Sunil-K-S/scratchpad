/**
 * LeetCode 79 — Word Search
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given an m×n character grid and a word, return true if the word exists in
 *   the grid as a connected path (adjacent cells horizontally/vertically).
 *   Each cell may only be used once per path.
 *
 *   Example: board=[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]
 *   word="ABCCED" → true
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: DFS + backtracking on grid
 * ─────────────────────────────────────────────────────────────────────────────
 *   For each cell that matches word[0], attempt a DFS.
 *   At each step: if current cell matches word[idx], recurse in all 4 directions.
 *   Mark cell as visited by temporarily replacing with '#', restore after recursion.
 *
 *   PRUNING: If board[r][c] != word[idx], return false immediately.
 *   BASE CASE: idx == word.size() → found the whole word, return true.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(m * n * 4^L) — L = word length; each path branches at most 4 ways
 *          (In practice much faster due to early termination.)
 *   SPACE: O(L) — recursion stack depth = word length
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Word longer than grid cells → false
 *   Word is single character → check if it appears anywhere
 *   Word requires revisiting the starting cell → prevented by '#' marking

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   DFS pattern matching on 2D grids appears in spatial and image processing:
 *   - OCR / handwriting recognition: locate a character sequence in a grid of
 *     character probabilities output by a neural network.
 *   - Circuit board inspection: search for a wire routing pattern on a PCB grid.
 *   - Game development: check if a valid word path exists on a Boggle / Scrabble
 *     board (this is exactly the Boggle solver problem).
 *   - Bioinformatics: search for a gene motif in a 2D representation of a
 *     protein folding grid.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool dfs(vector<vector<char>>& board, const string& word, int idx, int r, int c) {
    if (idx == static_cast<int>(word.size())) return true; // found entire word!

    const int rows = static_cast<int>(board.size());
    const int cols = static_cast<int>(board[0].size());
    if (r < 0 || r >= rows || c < 0 || c >= cols) return false; // out of bounds
    if (board[r][c] != word[idx]) return false;  // character mismatch

    char saved = board[r][c];
    board[r][c] = '#'; // mark as visited

    bool found = dfs(board, word, idx+1, r+1, c) ||
                 dfs(board, word, idx+1, r-1, c) ||
                 dfs(board, word, idx+1, r, c+1) ||
                 dfs(board, word, idx+1, r, c-1);

    board[r][c] = saved; // restore (backtrack)
    return found;
}

bool exist(vector<vector<char>>& board, const string& word) {
    for (int r = 0; r < static_cast<int>(board.size()); ++r) {
        for (int c = 0; c < static_cast<int>(board[0].size()); ++c) {
            if (dfs(board, word, 0, r, c)) return true;
        }
    }
    return false;
}

int main() {
    vector<vector<char>> b = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    std::cout << std::boolalpha << exist(b, "ABCCED") << '\n'; // true
    std::cout << exist(b, "SEE")    << '\n'; // true
    std::cout << exist(b, "ABCB")   << '\n'; // false (can't reuse B)
    return 0;
}
