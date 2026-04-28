/**
 * LeetCode 200 — Number of Islands
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given an m×n grid of '1' (land) and '0' (water), count the number of islands.
 *   An island is a group of '1's connected horizontally or vertically.
 *
 *   Example: [["1","1","0","0","0"],
 *             ["1","1","0","0","0"],
 *             ["0","0","1","0","0"],
 *             ["0","0","0","1","1"]]
 *   Output: 3
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: DFS/BFS flood fill
 * ─────────────────────────────────────────────────────────────────────────────
 *   Scan every cell. When you find a '1' (unvisited land):
 *   1. Increment island count.
 *   2. "Flood fill" — mark the entire connected island as visited by DFS/BFS.
 *      This prevents counting the same island twice.
 *
 *   Marking trick: overwrite '1' with '0' (or use a separate visited array).
 *   In-place mutation is fine here since we own the grid.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE
 * ─────────────────────────────────────────────────────────────────────────────
 *   (0,0)='1' → count=1, DFS floods (0,0),(0,1),(1,0),(1,1) → all become '0'
 *   (2,2)='1' → count=2, DFS floods (2,2)
 *   (3,3)='1' → count=3, DFS floods (3,3),(3,4)
 *   Answer: 3 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(m * n) — each cell visited at most once
 *   SPACE: O(m * n) — DFS recursion stack (worst case: entire grid is one island)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   All water → 0
 *   All land  → 1
 *   Single cell '1' → 1
 *
 * INTERVIEW TIP:
 *   This is the template for ALL grid DFS/BFS problems:
 *   LC 695 (max island area), LC 130 (surrounded regions), LC 286 (walls & gates),
 *   LC 994 (rotting oranges — BFS multi-source), LC 1162 (distance to nearest 0).
 *   Know it cold.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Connected component labeling in grids underpins many real systems:
 *   - Network segmentation: find isolated subnetworks in a network topology
 *     represented as an adjacency matrix.
 *   - Image processing: label connected regions of pixels (blob detection) for
 *     OCR, medical imaging, and computer vision pipelines.
 *   - Geography / GIS: count distinct land masses, water bodies, or
 *     administrative regions in a raster map.
 *   - Game development: flood-fill (paint bucket tool) and territory control
 *     in strategy games use exactly this DFS/BFS grid traversal.
 */

#include <iostream>
#include <vector>

using namespace std;

// DFS flood fill — marks all connected land from (r,c) as visited
void dfs(vector<vector<char>>& grid, int r, int c) {
    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());
    // Boundary check + already water/visited
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;
    grid[r][c] = '0'; // mark visited by sinking the land
    dfs(grid, r + 1, c);
    dfs(grid, r - 1, c);
    dfs(grid, r, c + 1);
    dfs(grid, r, c - 1);
}

int numIslands(vector<vector<char>>& grid) {
    int count = 0;
    for (int r = 0; r < static_cast<int>(grid.size()); ++r) {
        for (int c = 0; c < static_cast<int>(grid[0].size()); ++c) {
            if (grid[r][c] == '1') {
                ++count;
                dfs(grid, r, c); // flood fill this entire island
            }
        }
    }
    return count;
}

int main() {
    vector<vector<char>> g = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    std::cout << numIslands(g) << '\n'; // 3
    return 0;
}
