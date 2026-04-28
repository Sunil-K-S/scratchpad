/**
 * LeetCode 297 — Serialize and Deserialize Binary Tree
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Design an algorithm to serialize (tree → string) and deserialize
 *   (string → tree) a binary tree. The format is your choice.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Preorder DFS with null markers
 * ─────────────────────────────────────────────────────────────────────────────
 *   Serialize using preorder traversal. Represent null children as "#".
 *   This encoding uniquely identifies the tree structure because we record
 *   every null (unlike just recording values).
 *
 *   Tree:     1
 *            / \
 *           2   3
 *              / \
 *             4   5
 *
 *   Serialized: "1,2,#,#,3,4,#,#,5,#,#"
 *
 *   WHY preorder works for unique reconstruction:
 *   We know the first value is root. We know where left subtree ends because
 *   nulls tell us when a subtree is exhausted.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * DESERIALIZE PATTERN: Recursive with a token iterator/index
 * ─────────────────────────────────────────────────────────────────────────────
 *   Split string by delimiter, use a pointer/index into the token list.
 *   Each recursive call consumes exactly the tokens for that subtree.
 *   If token == "#" → return null.
 *   Else → create node, recurse left, recurse right.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) both serialize and deserialize
 *   SPACE: O(n) — string and recursion stack
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Empty tree (null root) → serialize as "#", deserialize back to null
 *   Single node            → "1,#,#"
 *   Negative values        → use comma delimiter so "-5" is unambiguous

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Tree serialization is essential in distributed systems and persistence:
 *   - Distributed caches (Redis, Memcached): store complex tree-structured objects
 *     (e.g., decision trees, parsed ASTs) as serialized byte strings.
 *   - Inter-process communication: serialize a parse tree to send over a network
 *     socket (gRPC uses Protocol Buffers which encode trees).
 *   - Machine learning: serialize trained decision tree / random forest models
 *     (scikit-learn pickle, ONNX format) for serving.
 *   - Configuration management: serialize hierarchical config trees (JSON/YAML
 *     are essentially text serializations of tree structures).
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
    int val; TreeNode* left; TreeNode* right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ── Serialize: preorder DFS, "#" for null ────────────────────────────────────
void serializeHelper(TreeNode* node, ostringstream& oss) {
    if (!node) { oss << "#,"; return; }
    oss << node->val << ',';
    serializeHelper(node->left, oss);
    serializeHelper(node->right, oss);
}

string serialize(TreeNode* root) {
    ostringstream oss;
    serializeHelper(root, oss);
    return oss.str(); // e.g. "1,2,#,#,3,4,#,#,5,#,#,"
}

// ── Deserialize: consume tokens one by one ───────────────────────────────────
TreeNode* deserializeHelper(vector<string>& tokens, int& idx) {
    if (idx >= static_cast<int>(tokens.size())) return nullptr;
    const string& token = tokens[idx++];
    if (token == "#") return nullptr;      // null marker
    TreeNode* node = new TreeNode(stoi(token));
    node->left  = deserializeHelper(tokens, idx); // consume left subtree
    node->right = deserializeHelper(tokens, idx); // consume right subtree
    return node;
}

TreeNode* deserialize(const string& data) {
    vector<string> tokens;
    stringstream ss(data);
    string token;
    while (getline(ss, token, ',')) { // split by ','
        if (!token.empty()) tokens.push_back(token);
    }
    int idx = 0;
    return deserializeHelper(tokens, idx);
}

// ── Verify: inorder of reconstructed tree should match original ──────────────
void inorder(TreeNode* root, vector<int>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left  = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left  = new TreeNode(4);
    root->right->right = new TreeNode(5);

    string s = serialize(root);
    std::cout << "Serialized: " << s << '\n'; // 1,2,#,#,3,4,#,#,5,#,#,

    TreeNode* restored = deserialize(s);
    vector<int> orig, rest;
    inorder(root, orig);
    inorder(restored, rest);
    std::cout << "Match: " << std::boolalpha << (orig == rest) << '\n'; // true
    return 0;
}
