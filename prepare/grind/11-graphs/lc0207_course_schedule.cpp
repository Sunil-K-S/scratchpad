/**
 * LeetCode 207 — Course Schedule
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   There are numCourses labeled 0 to n-1. prerequisites[i] = [a, b] means
 *   you must take course b before course a.
 *   Return true if it's possible to finish all courses (no cycle in the dependency graph).
 *
 *   Example: n=2, prerequisites=[[1,0]] → true (take 0 then 1)
 *   Example: n=2, prerequisites=[[1,0],[0,1]] → false (cycle: 0 needs 1, 1 needs 0)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Cycle detection via Topological Sort (Kahn's BFS)
 * ─────────────────────────────────────────────────────────────────────────────
 *   This is a directed graph cycle detection problem.
 *   If we can produce a valid topological ordering of all n courses → no cycle → true.
 *   If we can't (some nodes remain with in-degree > 0) → cycle → false.
 *
 *   KAHN'S ALGORITHM (BFS-based topo sort):
 *   1. Build adjacency list and in-degree count for each node.
 *   2. Add all nodes with in-degree 0 to a queue (they have no prerequisites).
 *   3. BFS: pop a node, "take" the course, decrement in-degree of all neighbors.
 *      If a neighbor's in-degree drops to 0, add it to the queue.
 *   4. Count how many courses were processed. If count == n → all courses taken → no cycle.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (n=4, prereqs=[[1,0],[2,0],[3,1],[3,2]])
 * ─────────────────────────────────────────────────────────────────────────────
 *   Graph: 0→1, 0→2, 1→3, 2→3
 *   In-degrees: {0:0, 1:1, 2:1, 3:2}
 *
 *   Queue: [0]  (in-degree 0)
 *   Pop 0: process. Neighbors 1,2: in-degree[1]=0, in-degree[2]=0 → add both.
 *   Count=1. Queue: [1,2]
 *
 *   Pop 1: process. Neighbor 3: in-degree[3]=1. Count=2. Queue: [2]
 *   Pop 2: process. Neighbor 3: in-degree[3]=0 → add. Count=3. Queue: [3]
 *   Pop 3: process. No neighbors. Count=4. Queue: []
 *
 *   Count==4==n → no cycle → true ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(V + E) — V = numCourses, E = prerequisites.size()
 *   SPACE: O(V + E) — adjacency list + in-degree array
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   No prerequisites → true (all courses independent)
 *   Self-loop [[0,0]] → false (in-degree[0] never reaches 0)
 *   Disconnected components → handled; each starts with in-degree 0 if no prereqs

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Topological sort / cycle detection in a DAG is fundamental to build systems:
 *   - Package managers (npm, pip, apt): resolve install order from dependency
 *     graphs; detect circular dependencies that would cause install failure.
 *   - Build systems (Make, Bazel, Gradle): compute task execution order so each
 *     task runs only after its prerequisites are complete.
 *   - Spreadsheet engines: determine cell evaluation order when cells reference
 *     each other; detect circular reference errors.
 *   - CI/CD pipelines: sequence pipeline stages (build -> test -> package -> deploy)
 *     using their dependency DAG.
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> in_degree(numCourses, 0);

    for (const auto& p : prerequisites) {
        adj[p[1]].push_back(p[0]); // edge: p[1] → p[0]
        in_degree[p[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (in_degree[i] == 0) q.push(i); // no prerequisites
    }

    int processed = 0;
    while (!q.empty()) {
        int course = q.front(); q.pop();
        ++processed;
        for (int next : adj[course]) {
            if (--in_degree[next] == 0) {
                q.push(next); // all prerequisites satisfied
            }
        }
    }
    return processed == numCourses; // if not all processed, there's a cycle
}

int main() {
    vector<vector<int>> p1 = {{1,0}};
    std::cout << std::boolalpha << canFinish(2, p1) << '\n'; // true

    vector<vector<int>> p2 = {{1,0},{0,1}};
    std::cout << canFinish(2, p2) << '\n'; // false (cycle)

    vector<vector<int>> p3 = {{1,0},{2,0},{3,1},{3,2}};
    std::cout << canFinish(4, p3) << '\n'; // true
    return 0;
}
