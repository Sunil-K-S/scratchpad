/**
 * LeetCode 102 — Binary Tree Level Order Traversal
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return the level-order (BFS) traversal as a list of lists, where each
 *   inner list contains values at the same depth.
 *
 *   Tree:      3
 *             / \
 *            9  20
 *              /  \
 *             15   7
 *
 *   Output: [[3], [9,20], [15,7]]
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: BFS with level size snapshot
 * ─────────────────────────────────────────────────────────────────────────────
 *   Standard BFS uses a queue. The trick to group by level:
 *   At the START of each level, snapshot queue.size() — that's how many nodes
 *   belong to the current level. Process exactly that many nodes, then all
 *   their children are the next level.
 *
 *   for each level:
 *     level_size = queue.size()
 *     for i in 0..level_size-1:
 *       node = queue.dequeue()
 *       add to current level list
 *       enqueue node->left, node->right if not null
 *     add current level list to result
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE
 * ─────────────────────────────────────────────────────────────────────────────
 *   Queue: [3]
 *   Level 1: size=1 → process 3, enqueue 9,20. result=[[3]]
 *   Queue: [9,20]
 *   Level 2: size=2 → process 9(no children), 20(enqueue 15,7). result=[[3],[9,20]]
 *   Queue: [15,7]
 *   Level 3: size=2 → process 15,7. result=[[3],[9,20],[15,7]]
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — each node enqueued/dequeued once
 *   SPACE: O(n) — queue holds at most one full level (widest level can be n/2 nodes)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Empty tree      → []
 *   Single node     → [[root_val]]
 *   Left-skewed     → [[1],[2],[3],...] (n levels, one node each)
 *
 * INTERVIEW TIP:
 *   BFS + level-size snapshot is the template for LC 103 (zigzag), LC 107
 *   (bottom-up), LC 199 (right side view), LC 637 (average per level).
 *   Same 10-line pattern, different what you do with each level's list.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   BFS / level-order traversal is used wherever shortest path or layered
 *   processing is needed:
 *   - Social networks: degrees of separation — BFS finds the shortest path
 *     between two users (LinkedIn 2nd connection feature).
 *   - Org chart rendering: display an org chart level-by-level, with each
 *     management layer on one row.
 *   - Web crawler: BFS ensures pages are crawled in order of link distance
 *     from the seed URL, prioritizing higher-quality pages.
 *   - Shortest path in unweighted graphs: BFS is the standard algorithm for
 *     word ladder, maze solving, and routing in hop-count networks.
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
    int val; TreeNode* left; TreeNode* right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int level_size = static_cast<int>(q.size()); // snapshot: nodes at current level
        vector<int> level;
        for (int i = 0; i < level_size; ++i) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(std::move(level));
    }
    return result;
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left  = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left  = new TreeNode(15);
    root->right->right = new TreeNode(7);

    for (auto& level : levelOrder(root)) {
        for (int x : level) std::cout << x << ' ';
        std::cout << '\n';
    }
    // 3
    // 9 20
    // 15 7
    return 0;
}
