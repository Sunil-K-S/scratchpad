/**
 * LeetCode 124 — Binary Tree Maximum Path Sum
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   A path in a binary tree is a sequence of nodes where each pair is connected
 *   by an edge. Each node appears at most once. The path does NOT need to pass
 *   through the root.
 *   Return the maximum sum of any path.
 *
 *   Example:       -10
 *                  /  \
 *                 9    20
 *                     /  \
 *                    15   7
 *   Max path: 15→20→7 = 42
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Two different "values" per node
 * ─────────────────────────────────────────────────────────────────────────────
 *   Every node has two roles:
 *
 *   1. "CONTRIBUTION to parent" — the max path going THROUGH this node and
 *      continuing UPWARD (can only extend in ONE direction: left OR right OR neither).
 *      gain(node) = node->val + max(0, gain(left), gain(right))
 *      (We take max with 0 to discard negative subtrees.)
 *
 *   2. "LOCAL BEST" — the best path that has this node as the HIGHEST point
 *      (the "roof"). This path CAN go left AND right (bends through this node).
 *      local = node->val + max(0, gain(left)) + max(0, gain(right))
 *
 *   We update the global answer with local at every node during DFS,
 *   but return only gain (contribution) to the parent.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE
 * ─────────────────────────────────────────────────────────────────────────────
 *   dfs(15): leaf. local=15, best=15. return gain=15.
 *   dfs(7):  leaf. local=7,  best=15. return gain=7.
 *   dfs(20): left_gain=15, right_gain=7.
 *     local = 20 + 15 + 7 = 42. best=42.
 *     return gain = 20 + max(15,7) = 35.
 *   dfs(9):  leaf. local=9. best=42. return gain=9.
 *   dfs(-10): left_gain=9, right_gain=35.
 *     local = -10 + max(0,9) + max(0,35) = -10+9+35 = 34. best stays 42.
 *     return gain = -10 + max(9,35) = 25. (not used further)
 *   Answer: 42 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — visit each node once
 *   SPACE: O(h) — recursion stack
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   All negative: [-3,-2,-1] → -1 (single node; we initialize best = INT_MIN)
 *   Single node:  [5] → 5
 *   Negative root with positive children: handled by max(0, gain) trick.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Max path through a tree generalizes to optimal route problems in hierarchies:
 *   - Network routing: find the highest-bandwidth path through a network
 *     topology tree (max-weight path in a tree = this problem).
 *   - Org chart analysis: find the most productive chain of employees
 *     from leaf contributor up through management to another leaf.
 *   - File system quota analysis: find the largest subtree sum of disk usage
 *     to identify which directory tree is consuming the most space.
 *   - Computational biology: find the highest-scoring alignment path through
 *     a phylogenetic tree.
 */

#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

struct TreeNode {
    int val; TreeNode* left; TreeNode* right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int best; // global max (use reference or class member in production)

// Returns the max "gain" this subtree can contribute to a parent path
int dfs(TreeNode* node) {
    if (!node) return 0;

    // Discard negative gains from children (taking them would reduce sum)
    int left_gain  = max(0, dfs(node->left));
    int right_gain = max(0, dfs(node->right));

    // Best path with this node as the highest point (can bend left+right)
    int local = node->val + left_gain + right_gain;
    best = max(best, local);

    // Return contribution upward: can only extend one direction
    return node->val + max(left_gain, right_gain);
}

int maxPathSum(TreeNode* root) {
    best = INT_MIN; // handles all-negative trees
    dfs(root);
    return best;
}

int main() {
    //    -10
    //    /  \
    //   9   20
    //       /  \
    //      15   7
    TreeNode* root = new TreeNode(-10);
    root->left  = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left  = new TreeNode(15);
    root->right->right = new TreeNode(7);
    std::cout << maxPathSum(root) << '\n'; // 42

    TreeNode* r2 = new TreeNode(-3);
    std::cout << maxPathSum(r2) << '\n'; // -3 (all negative)
    return 0;
}
