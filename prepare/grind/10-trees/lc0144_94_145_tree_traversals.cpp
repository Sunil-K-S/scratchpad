/**
 * LeetCode 144 / 94 / 145 — Binary Tree Traversals (Pre/In/Post order)
 * Difficulty: Easy
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given the root of a binary tree, return nodes in:
 *   144 — Preorder:  root → left → right
 *    94 — Inorder:   left → root → right
 *   145 — Postorder: left → right → root
 *
 *   Tree:      1
 *             / \
 *            2   3
 *           / \
 *          4   5
 *
 *   Preorder:  [1, 2, 4, 5, 3]
 *   Inorder:   [4, 2, 5, 1, 3]   ← for BST, inorder = sorted order
 *   Postorder: [4, 5, 2, 3, 1]
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * TWO APPROACHES: Recursive vs Iterative
 * ─────────────────────────────────────────────────────────────────────────────
 *   Recursive: trivial — follows definition directly. O(n) time, O(h) space.
 *   Iterative: uses explicit stack. Required when recursion depth is a problem
 *              or interviewer asks "can you do it without recursion?"
 *
 *   Iterative patterns differ for each traversal — know inorder iteratively
 *   as it appears in BST problems (e.g., LC 230 Kth Smallest in BST).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * INORDER ITERATIVE — The pattern to memorize
 * ─────────────────────────────────────────────────────────────────────────────
 *   curr = root
 *   while curr != null OR stack not empty:
 *     while curr != null:
 *       push curr
 *       curr = curr->left    (go as far left as possible)
 *     curr = stack.top(); pop
 *     visit curr             (process node)
 *     curr = curr->right     (then go right)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — visit each node exactly once
 *   SPACE: O(h) — h = tree height (O(log n) balanced, O(n) worst/skewed)

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Tree traversal order determines correctness in many systems:
 *   - Compilers: inorder traversal of an expression tree yields infix notation;
 *     postorder yields RPN (reverse Polish) for stack-based evaluation.
 *   - File systems: preorder traversal generates a directory listing (parent
 *     before children); postorder is needed to safely delete a directory tree.
 *   - DOM manipulation (browsers): preorder traversal visits HTML nodes in
 *     document order, matching CSS cascade and JavaScript event bubbling rules.
 *   - Serialization: preorder traversal serializes a BST in a way that can be
 *     deserialized back into the same structure.
 */

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ── Recursive traversals ─────────────────────────────────────────────────────
vector<int> preorderRec(TreeNode* root) {
    if (!root) return {};
    vector<int> res = {root->val};
    auto left  = preorderRec(root->left);
    auto right = preorderRec(root->right);
    res.insert(res.end(), left.begin(), left.end());
    res.insert(res.end(), right.begin(), right.end());
    return res;
}

void inorderRec(TreeNode* root, vector<int>& res) {
    if (!root) return;
    inorderRec(root->left, res);
    res.push_back(root->val);
    inorderRec(root->right, res);
}

void postorderRec(TreeNode* root, vector<int>& res) {
    if (!root) return;
    postorderRec(root->left, res);
    postorderRec(root->right, res);
    res.push_back(root->val);
}

// ── Iterative inorder (most important to know) ───────────────────────────────
vector<int> inorderIter(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    TreeNode* curr = root;
    while (curr != nullptr || !st.empty()) {
        // Go as far left as possible, pushing each node
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }
        // Process the leftmost unvisited node
        curr = st.top(); st.pop();
        res.push_back(curr->val);
        // Then explore its right subtree
        curr = curr->right;
    }
    return res;
}

// ── Iterative preorder ───────────────────────────────────────────────────────
vector<int> preorderIter(TreeNode* root) {
    if (!root) return {};
    vector<int> res;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top(); st.pop();
        res.push_back(node->val);       // visit
        if (node->right) st.push(node->right); // right first (LIFO → left processed first)
        if (node->left)  st.push(node->left);
    }
    return res;
}

void print(const vector<int>& v) {
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';
}

int main() {
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    TreeNode* root = new TreeNode(1);
    root->left  = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left  = new TreeNode(4);
    root->left->right = new TreeNode(5);

    print(preorderIter(root));  // 1 2 4 5 3
    print(inorderIter(root));   // 4 2 5 1 3
    vector<int> post; postorderRec(root, post); print(post); // 4 5 2 3 1
    return 0;
}
