/**
 * LeetCode 236 — Lowest Common Ancestor of a Binary Tree
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given root of a binary tree and two nodes p and q, find their LCA.
 *   LCA = the deepest node that is an ancestor of BOTH p and q.
 *   (A node is an ancestor of itself.)
 *
 *   Tree:          3
 *                /   \
 *               5     1
 *              / \   / \
 *             6   2 0   8
 *                / \
 *               7   4
 *
 *   LCA(5, 1) = 3   (root is lowest ancestor of both)
 *   LCA(5, 4) = 5   (5 is an ancestor of itself, and 4 is in 5's subtree)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Post-order DFS — search both subtrees first
 * ─────────────────────────────────────────────────────────────────────────────
 *   For each node, ask: "Is p or q in my left subtree? Right subtree?"
 *
 *   DFS returns a node or null:
 *   - If current node IS p or q → return current node (found one of them).
 *   - Recurse into left and right subtrees.
 *   - If BOTH left and right returned non-null → current node is LCA.
 *     (p and q are in different subtrees; current node is the split point.)
 *   - If only one side returned non-null → propagate that result upward.
 *     (Both p and q are in the same subtree; the LCA was found deeper.)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (LCA(5, 4) in tree above)
 * ─────────────────────────────────────────────────────────────────────────────
 *   dfs(3): recurse both sides
 *     dfs(5): node IS p(5) → return 5  (don't recurse deeper)
 *     dfs(1):
 *       dfs(0) → null (neither p nor q)
 *       dfs(8) → null
 *       return null
 *   Left returned 5, right returned null → return 5 (propagate upward)
 *   dfs(3) returns 5.
 *   Answer: 5 ✓
 *   (We returned 5 early without finding 4 — but that's fine: the problem
 *    guarantees both p and q exist, and since 5 IS p, and 4 is in 5's subtree,
 *    5 is the LCA by definition.)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — may visit every node in the worst case
 *   SPACE: O(h) — recursion stack; O(log n) balanced, O(n) skewed
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   p is ancestor of q (or vice versa): handled — we return p immediately,
 *   and since q is in p's subtree, p is the LCA.
 *   p == q: returns p (same node is its own ancestor).

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   LCA (lowest common ancestor) appears wherever hierarchy is central:
 *   - Git merge base: git merge-base A B finds the LCA of two commits in the
 *     commit DAG — the common ancestor used to compute the 3-way merge.
 *   - Taxonomy / ontology systems: find the most specific common category of
 *     two products in an e-commerce taxonomy (e.g., Electronics > Phones).
 *   - Network routing: find the nearest common router (LCA in a network tree)
 *     to determine optimal packet forwarding.
 *   - Compiler type systems: find the LCA in a class hierarchy to determine
 *     the most specific common supertype for type inference.
 */

#include <iostream>

struct TreeNode {
    int val; TreeNode* left; TreeNode* right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Base cases
    if (root == nullptr) return nullptr; // fell off tree
    if (root == p || root == q) return root; // found one target; return it

    // Search both subtrees
    TreeNode* left  = lowestCommonAncestor(root->left,  p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    // Both sides found something → this node is the split point = LCA
    if (left != nullptr && right != nullptr) return root;

    // Only one side found something → propagate it upward
    return (left != nullptr) ? left : right;
}

int main() {
    //       3
    //      / \
    //     5   1
    //    / \
    //   6   2
    //      / \
    //     7   4
    TreeNode* root = new TreeNode(3);
    root->left  = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left  = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left  = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    root->right->left  = new TreeNode(0);
    root->right->right = new TreeNode(8);

    TreeNode* p = root->left;             // node 5
    TreeNode* q = root->left->right->right; // node 4
    std::cout << lowestCommonAncestor(root, p, q)->val << '\n'; // 5

    q = root->right; // node 1
    std::cout << lowestCommonAncestor(root, p, q)->val << '\n'; // 3
    return 0;
}
